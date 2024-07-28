#ifndef _TGA_MEM_DIFF_STACK_H
#define _TGA_MEM_DIFF_STACK_H

#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>
#include "aligned_alloc.h"

// Allow user to customize allocators used if necessary
#ifndef MDS_CUSTOM_ALLOCATORS
#define MALLOC malloc
#define CALLOC calloc
#define REALLOC realloc
#define STRDUP strdup
#define FREE free
#define ALIGNED_MALLOC aligned_malloc
#define ALIGNED_REALLOC aligned_realloc
#define ALIGNED_FREE aligned_free
#endif

// Optimized subroutines for bitwise operations on aligned memory.
// TCC has no optimization, so we have to use simd manually
void memxor_simd(void* dest, void* src, size_t len);
void memor_simd(void* dest, void* src, size_t len);
void memandn_simd(void* dest, void* src, size_t len);
void memand_simd(void* dest, void* src, size_t len);
__asm__("

memxor_simd:
	xorq %rax, %rax
loop_xor_simd:
	movaps (%rcx, %rax), %xmm0
	pxor (%rdx, %rax), %xmm0
	movaps %xmm0, (%rcx, %rax)
	addq $0x10, %rax
	cmpq %rax, %r8
	ja loop_xor_simd
	ret

memor_simd:
	xorq %rax, %rax
loop_or_simd:
	movaps (%rcx, %rax), %xmm0
	por (%rdx, %rax), %xmm0
	movaps %xmm0, (%rcx, %rax)
	addq $0x10, %rax
	cmpq %rax, %r8
	ja loop_or_simd
	ret

memandn_simd:
	xorq %rax, %rax
loop_andn_simd:
	movaps (%rcx, %rax), %xmm0
	pandn (%rdx, %rax), %xmm0
	movaps %xmm0, (%rcx, %rax)
	addq $0x10, %rax
	cmpq %rax, %r8
	ja loop_andn_simd
	ret

memand_simd:
	xorq %rax, %rax
loop_and_simd:
	movaps (%rcx, %rax), %xmm0
	pand (%rdx, %rax), %xmm0
	movaps %xmm0, (%rcx, %rax)
	addq $0x10, %rax
	cmpq %rax, %r8
	ja loop_and_simd
	ret"
);

#define align16(n) (((n) + 0xF) & ~(uint64_t)0xF)


typedef struct _field_bitmask
{
	uint32_t offset;
	uint32_t uid; // to handle fields wider than 8 bytes (i.e. arrays). uid 0 indicates the terminator field
	uint64_t bitmask;
} field_bitmask;

typedef struct _mem_diff
{
	struct _mem_diff* next;
	void* diff_mask; // 16-byte aligned mask of bitwise diff (xor) between old/new mem
	void* field_mask; // 16-byte aligned mask of affected field bits
	uint32_t patch_uid; // unique id of related named patch, used to detect if merging is possible
} mem_diff;

// Stack of changes to a given memory block (in this case, param rows)
typedef struct _mem_diff_stack
{
	size_t region_size; // Region size, including extra from alignment requirements
	field_bitmask* field_defs;
	mem_diff* diff_stack_top;

	void* live_mem; // Target memory this diff will affect
	void* aligned_live_mem; // live_mem, aligned to 16 bytes
	void* temp_buffer; // 16-byte aligned
} mem_diff_stack;

// Create a mem diff stack tracking changes to a given block.
mem_diff_stack* mds_init(mem_diff_stack* mds, void* live_mem, size_t region_size, field_bitmask* field_defs)
{
	mds->region_size = align16(region_size + ((uintptr_t)live_mem & 0xF));
	mds->field_defs = field_defs;
	mds->diff_stack_top = NULL;
	mds->live_mem = live_mem;
	mds->aligned_live_mem = (void*)((uintptr_t)live_mem & ~(uintptr_t)0xF);
	mds->temp_buffer = ALIGNED_MALLOC(mds->region_size, 16);
	return mds;
}

// Register a new patch to the memory region. Will return a pointer to the live memory for modifications.
// Make sure to call mds_push_end immediately after modifications to save the diff.
void* mds_push_begin(mem_diff_stack* mds)
{
	memcpy(mds->temp_buffer, mds->aligned_live_mem, mds->region_size);
	return mds->live_mem;
}

// Finalize pushing a new memory change to the stack. If a new diff needs to be created,
// will return a pointer to it. Otherwise, returns NULL.
mem_diff* mds_push_end(mem_diff_stack* mds, uint32_t patch_uid)
{
	memxor_simd(mds->temp_buffer, mds->aligned_live_mem, mds->region_size);
	mem_diff* new_diff = NULL;

	// If the top block has the same patch_uid, merge them instead of creating a new block
	if (mds->diff_stack_top != NULL && mds->diff_stack_top->patch_uid == patch_uid)
		memxor_simd(mds->diff_stack_top, mds->temp_buffer, mds->region_size);
	// Otherwise, allocate a new block
	else
	{
		new_diff = (mem_diff*)MALLOC(sizeof(mem_diff));
		new_diff->next = mds->diff_stack_top;
		new_diff->diff_mask = ALIGNED_MALLOC(mds->region_size, 16);
		new_diff->field_mask = ALIGNED_MALLOC(mds->region_size, 16);
		new_diff->patch_uid = patch_uid;
		memcpy(new_diff->diff_mask, mds->temp_buffer, mds->region_size);
		memcpy(new_diff->field_mask, mds->temp_buffer, mds->region_size);
		mds->diff_stack_top = new_diff;
	}
	// Update the field mask if present
	if (mds->field_defs != NULL)
	{
		field_bitmask* fields = mds->field_defs;
		uintptr_t align_offset = (uintptr_t)mds->live_mem - (uintptr_t)mds->aligned_live_mem;
		uint8_t* diff_mask = (uint8_t*)mds->diff_stack_top->diff_mask + align_offset;
		uint8_t* field_mask = (uint8_t*)mds->diff_stack_top->field_mask + align_offset;

		for (int i = 0; fields[i].uid != 0;)
		{
			if (*(uint64_t*)(diff_mask + fields[i].offset) & fields[i].bitmask)
			{
				*(uint64_t*)(field_mask + fields[i].offset) |= fields[i].bitmask;

				for (int j = i - 1; j >= 0 && fields[j].uid == fields[i].uid; j--)
					*(uint64_t*)(field_mask + fields[j].offset) |= fields[j].bitmask;

				while (fields[i].uid == fields[++i].uid)
					*(uint64_t*)(field_mask + fields[i].offset) |= fields[i].bitmask;
			}
            else i++;
		}
	}
	return new_diff;
}

// Undo all changes in a given diff which are visible to the live object.
// "visible" regions are those not modified by a later memory edit.
// If the diff is on the top of the stack, O(region_size). Otherwise,
// O(depth * region_size). Returns TRUE if diff was found, FALSE otherwise.
bool mds_restore(mem_diff_stack* mds, mem_diff* diff)
{
	if (mds->diff_stack_top == NULL) return false;

	// If on top of stack, immediately apply changes to live memory and FREE the block
	if (mds->diff_stack_top == diff)
	{
		memxor_simd(mds->aligned_live_mem, diff->diff_mask, mds->region_size);
		ALIGNED_FREE(diff->diff_mask);
		ALIGNED_FREE(diff->field_mask);
		mds->diff_stack_top = diff->next;
		FREE(diff);
		return true;
	}

	// Otherwise, compute "hidden" changes mask by ORing field masks above diff
	memcpy(mds->temp_buffer, mds->diff_stack_top->field_mask, mds->region_size);
	mem_diff* curr = mds->diff_stack_top->next, * prev = mds->diff_stack_top;
	for (; curr != NULL && curr != diff; curr = (prev = curr)->next)
		memor_simd(mds->temp_buffer, curr->field_mask, mds->region_size);

	if (curr == NULL) return false;

	// Merge changes into the previous block
	memxor_simd(prev->diff_mask, curr->diff_mask, mds->region_size);
	memor_simd(prev->field_mask, curr->field_mask, mds->region_size);

	// Remove parts of merged changes that will be reverted now, i.e. only keep merged "hidden" changes
	memand_simd(prev->diff_mask, mds->temp_buffer, mds->region_size);
	memand_simd(prev->field_mask, mds->temp_buffer, mds->region_size);

	// ANDN "hidden" changes mask with diff mask and apply to live mem
	memandn_simd(mds->temp_buffer, diff->diff_mask, mds->region_size);
	memxor_simd(mds->aligned_live_mem, mds->temp_buffer, mds->region_size);

	// Free the unused block
	prev->next = curr->next;
	ALIGNED_FREE(curr->diff_mask);
	ALIGNED_FREE(curr->field_mask);
	FREE(curr);

	return true;
}

#endif