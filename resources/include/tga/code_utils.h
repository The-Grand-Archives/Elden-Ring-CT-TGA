#ifndef _TGA_CODE_UTILS
#define _TGA_CODE_UTILS

#include <winapi/windows.h>
#include <stdbool.h>

#include "hde/hde64.h"
#include "vector.h"

typedef struct _relocated_fn_info {
    void* code_begin;
    void* function_begin;
    size_t code_size;
} relocated_fn_info;

// Performs control flow analysis of a function, and relocates its code
// to some other block of memory. Can be used to call a modified game function without 
// triggering the anti-cheat. 
//
// Returns false if not enough memory. In this case, info_out_opt->code_size will be set
// to the required amount of memory.
bool code_reloc(void* function, relocated_fn_info* info_out_opt, void* dest, size_t dest_size)
{
    // TODO: Implement!
    return false;
}

#endif