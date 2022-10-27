#ifndef _TGA_PATTERN
#define _TGA_PATTERN

#include <stdint.h>
#include <stdbool.h>
#include "mem_region.h"

/// Check if the memory at addresses matches the given pattern after application of a bitmask
inline bool matches_pattern(const uint8_t* addr, const uint8_t* pat, const uint8_t* mask, int size) {
    const uint8_t* end = addr + size;
    for (; addr < end; addr++, pat++, mask++) {
        if ((*addr ^ *pat) & *mask) return false;
    }
    return true;
}

/// Find all memory addresses in region matching the given memory pattern after application of a bitmask
inline int pattern_search(const region* reg, const uint8_t* pat, const uint8_t* mask, int size, intptr_t* out_array, int out_array_size) {
    if (out_array_size == 0)
        return 0;

    int num_out = 0;
    const uint8_t* addr = (const uint8_t*)reg->base;
    const uint8_t* end = (const uint8_t*)(reg->base + reg->size - sizeof(pat));
    for (; addr <= end && num_out < out_array_size; addr++) {
        if (!matches_pattern(addr, pat, mask, sizeof(pat))) continue;
        out_array[num_out++] = (intptr_t)addr;
    }
    return num_out;
}

/// Find the first memory addresses in region matching the given memory pattern after application of a bitmask,
/// or zero if not found. 
inline intptr_t pattern_search_unique(const region* reg, const uint8_t* pat, const uint8_t* mask, int size) {
    const uint8_t* addr = (const uint8_t*)reg->base;
    const uint8_t* end = (const uint8_t*)(reg->base + reg->size - sizeof(pat));
    for (; addr <= end; addr++) {
        if (!matches_pattern(addr, pat, mask, sizeof(pat))) return (intptr_t)addr;
    }
    return 0;
}

#endif