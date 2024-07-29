#ifndef _TGA_SAFE_PTR_READ
#define _TGA_SAFE_PTR_READ

#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

#include <winapi/windows.h>
#include <winnt.h>

#include "celua.h"

// Handle to vectored exception handler used internally to handle access violations.
PVOID _BAD_PTR_VEH_HANDLE = NULL;

bool _safe_ptr_do_read(void* ptr, uint64_t* out_value);
void _safe_ptr_exception_point();
void _safe_ptr_do_read_end();
__asm__("
    _safe_ptr_do_read:
        xorb %al, %al
        movq (%rcx), %r8
    _safe_ptr_exception_point:
        movq %r8, (%rdx)
        movb $1, %al
    _safe_ptr_do_read_end:
        ret
    "
);

LONG _safe_ptr_veh_handler(uint8_t* ExceptionInfo)
{
    // I fucking hate TCC
    // It gets confused with the fact that CONTEXT is 16-byte aligned and aligns 
    // the POINTER at 16 bytes to, so we have to do this garbage

    EXCEPTION_RECORD* rec = *(EXCEPTION_RECORD**)ExceptionInfo;
    CONTEXT* ctx = *(CONTEXT**)(ExceptionInfo + 8);

    uintptr_t addr = (uintptr_t)rec->ExceptionAddress;
    if (addr > (uintptr_t)_safe_ptr_do_read && addr <= (uintptr_t)_safe_ptr_exception_point) {
        ctx->Rip = (DWORD64)_safe_ptr_do_read_end;
        return EXCEPTION_CONTINUE_EXECUTION;
    }
    return EXCEPTION_CONTINUE_SEARCH;
}

void safe_ptr_register_handler()
{
    if (!_BAD_PTR_VEH_HANDLE) {
        _BAD_PTR_VEH_HANDLE = AddVectoredExceptionHandler(TRUE, _safe_ptr_veh_handler);
    }
}

void safe_ptr_unregister_handler()
{
    if (_BAD_PTR_VEH_HANDLE) {
        RemoveVectoredExceptionHandler(_BAD_PTR_VEH_HANDLE);
        _BAD_PTR_VEH_HANDLE = NULL;
    }
}

// "perfect hashing" based cache of invalid pages 
// The hash doesn't actually need to be perfect, just to have a low enough chance 
// of collisions to reduce the amount of segfaults that will occur effectively
// expected rate of collisions is 1/sqrt(cache_size)
typedef struct _bad_page_cache {
    uintptr_t* addr_cache;
    size_t cache_size; // Should be a prime number
    uint64_t total_bad_reads; // For debugging / perf. evaluation purposes
} bad_page_cache;

// naive primality test
bool is_prime(uint64_t n) 
{
    if (!(n & 1)) return false;
    for (uint64_t i = 3; i * i <= n; i += 2) {
        if (n % i == 0) return false;
    }
    return true;
}

// Creates a page access cache used to keep track of invalid memory regions. 
void bad_page_cache_init(bad_page_cache* cache, size_t requested_size) 
{
    requested_size |= 1;
    while (!is_prime(requested_size)) {
        requested_size += 2;
    }

    cache->addr_cache = (uintptr_t*)calloc(requested_size, sizeof(uintptr_t));
    cache->cache_size = requested_size;
    cache->total_bad_reads = 0;
}

// Destroys a page access cache used to keep track of invalid memory regions, freeing internal memory. 
void bad_page_cache_destroy(bad_page_cache* cache) 
{
    if (cache->addr_cache) free(cache->addr_cache);
    cache->addr_cache = NULL;
    cache->cache_size = 0;
}

// Safely read from a potentially invalid pointer ptr, writing the value into out_value. 
// We assume ptr is 8-byte aligned so that the value fits entirely in a page. If this is not
// the case, cache performance will be poor. 
bool safe_ptr_read(bad_page_cache* cache, void* ptr, uint64_t* out_value) {
    *out_value = 0;
    // First perform obvious usermode memory pointer validity check
    if ((uintptr_t)ptr < 0x10000 || (uintptr_t)ptr > 0x0007FFFFFFFFFFFF)
        return false;

    // Store cached data in table as (page_index << 1) | readability
    uintptr_t page_index = (uintptr_t)ptr >> 12;
    size_t key = page_index % cache->cache_size;

    // If cached invalid page is indeed the current one, consider memory invalid and return
    if (cache->addr_cache[key] == page_index)
        return false;

    // Otherwise, we have to actually read the value and possibly cache it as invalid
    if (_safe_ptr_do_read(ptr, out_value)) {
        cache->addr_cache[key] = 0; // Clear address cache for valid page
        return true;
    }
    else {
        cache->addr_cache[key] = page_index; // Write page index into cache (invalid)
        cache->total_bad_reads++;
        return false;
    }
}

#endif