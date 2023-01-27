#ifndef _TGA_PATTERN
#define _TGA_PATTERN

#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include "mem_region.h"

// Byte pattern which can be 
typedef struct _pattern {
    uint8_t* bytes;
    uint8_t* mask;
    size_t size;
} pattern;

// Tries to convert an hexadecimal digit to its integer value. 
// Returns -1 when the character is not a valid hexadecimal digit (a-fA-F0-9). 
#define HEX_CHAR_TO_NUM(hex) ({ \
    char ret = -1; \
    char h = hex; \
    if (h >= '0' && h <= '9') ret = h - '0'; \
    else if (h >= 'a' && h <= 'f') ret = 10 + h - 'a'; \
    else if (h >= 'A' && h <= 'F') ret = 10 + h - 'A'; \
    ret; \
}) \

// Initializes a pattern from a CE AOB-like string. 
bool pattern_init(pattern* pat, const char* ce_aob_string) {
    size_t len = strlen(ce_aob_string);
    pat->bytes = malloc(len); // Allocate upper bound
    pat->mask = malloc(len);
    pat->size = 0;
    
    for (const char* c = ce_aob_string; c[0]; c++) {
        if (c[0] == ' ') continue;
        else if (!c[1] || c[1] == ' ') {
            char b = HEX_CHAR_TO_NUM(c[0]);
            if (b < 0 && c[0] != '?')
                return false;
            pat->bytes[pat->size] = b;
            pat->mask[pat->size++] = b == -1 ? 0 : 0xff;
        }
        else if (c[1]) {
            char c1 = HEX_CHAR_TO_NUM(c[0]), c2 = HEX_CHAR_TO_NUM(c[1]);
            if (c1 < 0 && c[0] != '?')
                return false;
            if (c2 < 0 && c[1] != '?')
                return false;

            pat->bytes[pat->size] = (c1 & 0xF) << 4 | (c2 & 0xF);
            pat->mask[pat->size++] = (c1 < 0 ? 0 : 0xf0) | (c2 < 0 ? 0 : 0xf);
            c++;
        }
    }
    return true;
}

// Frees memory dynamically allocated when creating a pattern.
void pattern_destroy(pattern* pat) {
    free(pat->bytes);
    free(pat->mask);
}

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
    const uint8_t* end = (const uint8_t*)(reg->base + reg->size - size);
    for (; addr <= end && num_out < out_array_size; addr++) {
        if (!matches_pattern(addr, pat, mask, size)) continue;
        out_array[num_out++] = (intptr_t)addr;
    }
    return num_out;
}

/// Find the first memory addresses in region matching the given memory pattern after application of a bitmask,
/// or zero if not found. 
inline intptr_t pattern_search_unique(const region* reg, const uint8_t* pat, const uint8_t* mask, int size) {
    const uint8_t* addr = (const uint8_t*)reg->base;
    const uint8_t* end = (const uint8_t*)(reg->base + reg->size - size);
    for (; addr <= end; addr++) {
        if (matches_pattern(addr, pat, mask, size)) return (intptr_t)addr;
    }
    return 0;
}

// Returns the address of the first match of a CE AOB string in given module section.
// Shortcut to the boilerplate of pattern_init + region_from_module + pattern_seach_unique.
intptr_t easy_aob_scan(const char* module, const char* section, const char* aob) {
    region reg;
    if (!region_from_module(&reg, module, section)) return 0;

    pattern pat;
    if (!pattern_init(&pat, aob)) {
        pattern_destroy(&pat);
        return 0;
    }

    intptr_t addr = pattern_search_unique(&reg, pat.bytes, pat.mask, pat.size);
    pattern_destroy(&pat);
    return addr;
}

#endif