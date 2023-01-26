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
// Returns false if not enough memory. In this case, info_out_opt->code_size will be set
// to the required amount of memory.
bool code_reloc(uintptr_t function, relocated_fn_info* info_out_opt, void* dest, size_t dest_size)
{
    relocated_fn_info info = { 
        .code_begin = 0, 
        .code_end = UINTPTR_MAX, 
        .function_begin = function 
    };

    typedef struct _reloc {
        uintptr_t instr_base;
        uint8_t imm32_ofs; 
        uint8_t instr_len;
    } reloc;

    VECTOR(uintptr_t)* ip_stack = VECTOR_CREATE(uintptr_t, NULL, NULL);
    VECTOR(reloc)* relocs = VECTOR_CREATE(reloc, NULL, NULL);

    VECTOR_PUSH(ip_stack, function);

    HASHMAP(uintptr_t, bool)* visited = HASHMAP_CREATE_COPY(uintptr_t, bool, hm2_u64_hash, hm2_u64_eq);

    hde64s instr;
    while (ip_stack->size > 0) {
        uintptr_t ip = VECTOR_POP(ip_stack);
        if (HASHMAP_INSERT(visited, ip, true, NULL)) continue;
        
        hde64_disasm((void*)ip, &instr);

        // TODO:
        // Check if short JMP/JCC, if so follow and update code begin/end
        // If long (>4K bytes) JMP/JCC, CALL or MOD.RM RIP-relative memory access, add to relocation list 
    }

    VECTOR_DELETE(ip_stack);
    HASHMAP_DELETE(visited);

    return false;
}

#endif