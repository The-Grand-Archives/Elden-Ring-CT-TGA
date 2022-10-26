#ifndef _TGA_MEM_REGION
#define _TGA_MEM_REGION

#include <stdint.h>

/// Represents a 32-bit relative offset from module base. 
typedef uint32_t ibo32;

typedef struct _region {
    uintptr_t base;
    uint32_t size;
} region;

/// Check if a pointer lies a given region, taking the pointer's size into account.
#define ptr_in_region(ptr, reg) \
    ((uintptr_t)(ptr) >= (uintptr_t)((region*)(reg))->base && \
     (uintptr_t)(ptr) <= (uintptr_t)((region*)(reg))->base + ((region*)(reg))->size - sizeof(typeof(ptr)))

/// Check if a relative offset lies a given region, taking the pointer's size into account.
#define ibo32_in_region(offset, reg) \
    ((offset) >= 0 && (offset) < ((region*)(reg))->size)

/// Get pointer from a module relative offset
#define ibo32_get_ptr(offset, reg) ((uintptr_t)((region*)(reg))->base + (offset))

/// Quickly eliminate a value being a pointer
#define isptr_heuristic(addr) ( \
    (uintptr_t)(addr) >= 0x10000 && \
    (uintptr_t)(addr) < 0x0000800000000000ull)

#endif