#ifndef _TGA_CODE_UTILS
#define _TGA_CODE_UTILS

#include <winapi/windows.h>
#include <stdbool.h>

#include <hde/hde64.h>
#include <winnt.h>
#include "stdint.h"
#include "vector.h"
#include "hashmap2.h"

// Allocates a block of SIZE bytes such that every address in [REGION_START, REGION_END] is within near jmp distance
// of every address in the allocated block.
void* virtual_alloc_near(size_t desired_size, DWORD protect, intptr_t region_start, intptr_t region_end)
{
    SYSTEM_INFO sinfo;
    GetSystemInfo(&sinfo);

    size_t gran = sinfo.dwAllocationGranularity;

    // Round size and boundaries to allocation granularity (64KB)
    desired_size = (desired_size + gran - 1) & ~(gran - 1);
    region_start &= ~(gran - 1);
    region_end = (region_end + gran - 1) & ~(gran - 1);

    // compute lowest possible allocation address (note that the [0, 64K) block is not usable)
    const intptr_t max_dist = (intptr_t)1 << 31;
    intptr_t addr = max(region_end - max_dist, (intptr_t)sinfo.dwAllocationGranularity);

    MEMORY_BASIC_INFORMATION minfo;
    while (VirtualQuery((void*)addr, &minfo, sizeof(minfo))) {
        if (minfo.State != MEM_FREE) continue;

        intptr_t base = (intptr_t)minfo.BaseAddress;
        intptr_t size = (intptr_t)minfo.RegionSize;
        addr = base + size;

        // not enough space for the memory block
        if (size < desired_size) continue;

        intptr_t chosen_base = 0;
        // Case 1: below the region and furthest address in range
        if (addr <= region_start && region_end + desired_size - addr <= max_dist) {
            chosen_base = addr - desired_size;
        } 
        // Case 2: above the region and furthest address in range
        else if (base >= region_end && base + desired_size - region_start <= max_dist) {
            chosen_base = base;
        }
        // range of pages is not suitable
        else continue;

        return VirtualAlloc((void*)chosen_base, desired_size, MEM_RESERVE | MEM_COMMIT, protect);
    }
    return NULL;
}

typedef struct _fn_info {
    uintptr_t code_begin;
    uintptr_t code_end;
    uintptr_t function_begin;
} fn_info;

// Performs control flow analysis of a function, and relocates its code
// to some other block of memory (within near jmp distance). Can be used to 
// call a modified game function without triggering the anti-cheat. 
//
// If DEST is null, the function will attempt to allocate its own block of memory.
// This block must be freed after use with VirtualFree.
//
// Returns false if code analysis failed or not enough memory. In this case, 
// info->code_size will be set to the required amount of memory. 
bool code_reloc(fn_info* original, fn_info* relocated, void* dest, size_t dest_size)
{
    original->code_begin = UINTPTR_MAX;
    original->code_end = 0;

    typedef struct _reloc {
        uint64_t instr_end;
        int64_t imm;
        uint8_t imm_size;
    } reloc;

    VECTOR(reloc)* relocs = VECTOR_CREATE(reloc, NULL, NULL);
    HASHMAP(uintptr_t, bool)* visited = HASHMAP_CREATE_COPY(uintptr_t, bool, hm2_u64_hash, hm2_u64_eq);
    
    VECTOR(uintptr_t)* ip_stack = VECTOR_CREATE(uintptr_t, NULL, NULL);
    VECTOR_PUSH(ip_stack, original->function_begin);
    bool result = false;
    hde64s instr;

    while (ip_stack->size > 0) {
        uintptr_t ip = VECTOR_POP(ip_stack);
        if (HASHMAP_INSERT(visited, ip, true, NULL)) continue;
        
        hde64_disasm((void*)ip, &instr);
        if (instr.flags & F_ERROR) { original->function_begin = 0; goto ret; }

        if (ip < original->code_begin) original->code_begin = ip;
        if (ip > original->code_end) original->code_end = ip + instr.len;

        reloc r = { .instr_end = ip + instr.len };
        
        if (instr.flags & F_RELATIVE) {
            r.imm_size = (instr.flags & (2 * F_IMM64 - 1)) / F_IMM8;

            if (instr.flags & F_IMM8) r.imm = instr.imm.imm8;
            else if (instr.flags & F_IMM16) r.imm = instr.imm.imm16;
            else if (instr.flags & F_IMM32) r.imm = instr.imm.imm32;
            else r.imm = instr.imm.imm64;
            
            if (instr.opcode == 0xE8) {
                VECTOR_PUSH(relocs, r);
            }
            
            // if not an unconditional flow instruction or call, continue to next instruction
            if (!(instr.opcode == 0xEB || instr.opcode == 0xE9)) {
                VECTOR_PUSH(ip_stack, ip + instr.len);
            }
            // otherwise, follow jmp path
            if (instr.opcode != 0xE8) {
                VECTOR_PUSH(ip_stack, ip + instr.len + r.imm);
            }
            continue;
        }
        else if ((instr.flags & F_MODRM) && instr.modrm_mod == 0 && instr.modrm_rm == 0b101) {
            r.imm = instr.disp.disp32;
            r.imm_size = 4;
            VECTOR_PUSH(relocs, r);
        }
        else if (instr.opcode == 0xC3) continue;

        VECTOR_PUSH(ip_stack, ip + instr.len);
    }

    size_t code_size = original->code_end - original->code_begin;

    if (dest == NULL) {
        dest = virtual_alloc_near(code_size, PAGE_EXECUTE_READWRITE, original->code_begin, original->code_end);
        dest_size = code_size;
    }
    if (dest == NULL) goto ret;

    // Destination buffer is too small to store the function
    if (code_size > dest_size) {
        goto ret;
    }

    int64_t ofs = (uintptr_t)dest - original->code_begin;
    relocated->code_begin = (uintptr_t)dest;
    relocated->code_end = (uintptr_t)dest + code_size; 
    relocated->function_begin = original->function_begin + ofs;

    // Write code
    memcpy(dest, (void*)original->code_begin, code_size);

    // Perform relocations
    for (size_t i = 0; i < relocs->size; i++) {
        reloc* r = relocs->data + i;
        int64_t new_imm = r->imm - ofs;

        memcpy((uint8_t*)r->instr_end + ofs - r->imm_size, &new_imm, r->imm_size); 
    }

    result = true;

ret:
    VECTOR_DELETE(relocs);
    VECTOR_DELETE(ip_stack);
    HASHMAP_DELETE(visited);
    return result;
}

typedef struct _call_hook { 
    void* original;
    void* hook;
    uint8_t* thunk;
    uint8_t* call_instr;
    bool is_manual_thunk;
} call_hook;

// A typed call hook object created from an argument list e.g. CALL_HOOK(void, (int, float, char*))
#define CALL_HOOK(ftype) typeof(struct { \
    typeof(ftype) original; \
    typeof(ftype) hook; \
    uint8_t* thunk; \
    uint8_t* call_instr; \
    bool is_manual_thunk; \
})

// install a call hook which will redirect the given call instruction to the hook.
// thunk must be AT LEAST 12 bytes. If null, one will be auto allocated.
bool call_hook_install(call_hook* ch, void* call_instr, void* thunk) {
    if (!thunk) {
        thunk = virtual_alloc_near(12, PAGE_EXECUTE_READWRITE, (intptr_t)call_instr, (intptr_t)call_instr + 5);
        ch->is_manual_thunk = false;
        ch->thunk = thunk;
        if (!thunk) return false;
    }
    else ch->is_manual_thunk = true;

    intptr_t icall = (intptr_t)call_instr, ithunk = (intptr_t)thunk;
    ch->original = (void*)(icall + 5 + *(int32_t*)(icall + 1));
    ch->call_instr = (uint8_t*)icall;
    ch->thunk = thunk;

    // movabs rax, hook
    *(uint16_t*)(ithunk + 0) = 0xB848;
    *(void**)(ithunk + 2) = ch->hook;
    // jmp rax
    *(uint16_t*)(ithunk + 10) = 0xE0FF;

	DWORD oldProtect;
	VirtualProtect(call_instr, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(int32_t*)(icall + 1) = ithunk - (icall + 5);
	VirtualProtect(call_instr, 5, oldProtect, &oldProtect);

    return true;
}

// uninstall a call hook.
void call_hook_uninstall(call_hook* ch) {
    DWORD oldProtect;
	VirtualProtect(ch->call_instr, 5, PAGE_EXECUTE_READWRITE, &oldProtect);
    *(int32_t*)(ch->call_instr + 1) = (intptr_t)ch->original - (intptr_t)(ch->call_instr + 5);
	VirtualProtect(ch->call_instr, 5, oldProtect, &oldProtect);

    if (!ch->is_manual_thunk) {
        VirtualFree(ch->thunk, 0, MEM_RELEASE);
        ch->thunk = 0;
    }
}

#endif