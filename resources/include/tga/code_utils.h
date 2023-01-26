#ifndef _TGA_CODE_UTILS
#define _TGA_CODE_UTILS

#include <winapi/windows.h>
#include <stdbool.h>

#include <hde/hde64.h>
#include "stdint.h"
#include "vector.h"
#include "hashmap2.h"

typedef struct _relocated_fn_info {
    uintptr_t code_begin;
    uintptr_t code_end;
    uintptr_t function_begin;
} relocated_fn_info;

// Performs control flow analysis of a function, and relocates its code
// to some other block of memory. Can be used to call a modified game function without 
// triggering the anti-cheat. 
//
// Returns false if not enough memory. In this case, info->code_size will be set
// to the required amount of memory.
bool code_reloc(uintptr_t function, relocated_fn_info* info, void* dest, size_t dest_size)
{
    info->code_begin = 0, 
    info->code_end = UINTPTR_MAX, 
    info->function_begin = function;

    typedef struct _reloc {
        uint64_t instr_end;
        int64_t imm;
        uint8_t imm_size;
    } reloc;

    VECTOR(reloc)* relocs = VECTOR_CREATE(reloc, NULL, NULL);
    HASHMAP(uintptr_t, bool)* visited = HASHMAP_CREATE_COPY(uintptr_t, bool, hm2_u64_hash, hm2_u64_eq);
    
    VECTOR(uintptr_t)* ip_stack = VECTOR_CREATE(uintptr_t, NULL, NULL);
    VECTOR_PUSH(ip_stack, function);
    bool result = false;
    hde64s instr;

    while (ip_stack->size > 0) {
        uintptr_t ip = VECTOR_POP(ip_stack);
        if (HASHMAP_INSERT(visited, ip, true, NULL)) continue;
        
        hde64_disasm((void*)ip, &instr);
        if (instr.flags & F_ERROR) { info->function_begin = 0; goto ret; }

        if (ip < info->code_begin) info->code_begin = ip;
        if (ip > info->code_end) info->code_end = ip;

        reloc r = { .instr_end = ip + instr.len };
        
        if (instr.flags & F_RELATIVE) {
            r.imm_size = (instr.flags & (2 * F_IMM64 - 1)) / F_IMM8;

            if (instr.flags & F_IMM8) r.imm = instr.imm.imm8;
            else if (instr.flags & F_IMM16) r.imm = instr.imm.imm16;
            else if (instr.flags & F_IMM32) r.imm = instr.imm.imm32;
            else r.imm = instr.imm.imm64;
            
            if (r.imm > 4096 || instr.opcode == 0xE8) {
                VECTOR_PUSH(relocs, r);
            }
            
            bool unconditional = instr.opcode == 0xEB || instr.opcode == 0xE9;
            // if not an unconditional flow instruction and immediate not too large, continue
            if (!unconditional && (instr.opcode == 0xE8 || r.imm <= 4096)) {
                VECTOR_PUSH(ip_stack, ip + instr.len);
            }
            // otherwise, follow jmp path
            if (instr.opcode != 0xE8 && r.imm <= 4096) {
                VECTOR_PUSH(ip_stack, ip + instr.len + r.imm);
            }
            continue;
        }
        else if (instr.flags & F_MODRM && instr.modrm_mod == 0 && instr.modrm_rm == 0b101) {
            VECTOR_PUSH(relocs, r);
        }
        else if (instr.opcode == 0xC3) continue;

        VECTOR_PUSH(ip_stack, ip + instr.len);
    }

    // Destination buffer is too small to store the function
    if (info->code_end - info->code_begin > dest_size) {
        goto ret;
    }

    // Write code
    memcpy(dest, (void*)info->code_begin, info->code_end - info->code_begin);

    // Perform relocations
    int64_t ofs = (uintptr_t)dest - info->code_begin;
    for (size_t i = 0; i < relocs->size; i++) {
        reloc* r = relocs->data + i;
        int64_t new_imm = r->imm + ofs;

        memcpy((uint8_t*)r->instr_end + info->code_begin - r->imm_size, &new_imm, r->imm_size); 
    }

    result = true;

ret:
    VECTOR_DELETE(relocs);
    VECTOR_DELETE(ip_stack);
    HASHMAP_DELETE(visited);
    return result;
}

#endif