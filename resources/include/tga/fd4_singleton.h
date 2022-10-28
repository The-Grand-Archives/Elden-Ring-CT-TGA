#ifndef _TGA_FD4_SINGLETON
#define _TGA_FD4_SINGLETON

#include "mem_region.h"
#include "pattern.h"
#include "bsearch.h"

// Find all unique singleton addresses by searching for null singleton checks in a memory region.
int find_singleton_addresses(const region* reg, intptr_t* out_array, int out_array_size) {
    /* matches the following instruction pattern with registers and addresses masked out
       140aa2a39 48 8b 0d        MOV        RCX,qword ptr [DAT_143c65b38]                    = ??
                 f8 30 1c 03
       140aa2a40 48 85 c9        TEST       RCX,RCX
       140aa2a43 75 2e           JNZ        LAB_140aa2a73
       140aa2a45 48 8d 0d        LEA        RCX,[DAT_143c42a19]                              = ??
                 cd ff 19 03
       140aa2a4c e8 0f a5        CALL       FUN_141e2cf60                                    undefined FUN_141e2cf60()
                 38 01
    */
    static const uint8_t aob[] =  { 0x48, 0x8b, 0x0d, 0xf8, 0x30, 0x1c, 0x03, 0x48, 0x85, 0xc9, 0x75, 0x2e, 0x48, 0x8d, 0x0d, 0xcd, 0xff, 0x19, 0x03, 0xe8, 0x0f, 0xa5, 0x38, 0x01 };
    static const uint8_t mask[] = { 0xFF, 0xFF, 0xC7, 0x00, 0x00, 0x00, 0x00, 0xFF, 0xFF, 0xC0, 0xFF, 0x00, 0xFF, 0xFF, 0xC7, 0x00, 0x00, 0x00, 0x00, 0xFF, 0x00, 0x00, 0x00, 0x00 };

    if (out_array_size == 0)
        return 0;

    int num_out = 0;
    const uint8_t* addr = (const uint8_t*)reg->base;
    const uint8_t* end = (const uint8_t*)(reg->base + reg->size - sizeof(aob));
    for (; addr <= end; addr++) {
        if (!matches_pattern(addr, aob, mask, sizeof(aob))) continue;

        // Read singleton address from MOV instruction relative offset
        intptr_t s = (intptr_t)addr + 7 + *(uint32_t*)(addr + 3);

        int insert_at = bsearch_geq(s, out_array, num_out);
        if (insert_at < num_out && out_array[insert_at] == s) continue;

        // Shift elements above new one up one index to make space
        for (int j = num_out - 1; j >= insert_at; --j)
            out_array[j+1] = out_array[j];
        out_array[insert_at] = s;

        if (++num_out == out_array_size)
            break;
    }
    return num_out;
}

#endif