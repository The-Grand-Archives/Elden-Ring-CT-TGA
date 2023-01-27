#ifndef _TGA_MEM_REGION
#define _TGA_MEM_REGION

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <winapi/windows.h>

/// Represents a 32-bit relative offset from module base. 
typedef uint32_t ibo32;

typedef struct _region {
    uintptr_t base;
    uint32_t size;
} region;

// Creates a region struct from a module (DLL/EXE) and PE section name.
// Passing a null module name targets the main executable module, and passing
// a null section name creates a region encompassing the entire module.  
bool region_from_module(region* region_out, const char* module_name, const char* section_name) {
    HINSTANCE handle = GetModuleHandleA(module_name);
    if (!handle) return false;

    IMAGE_DOS_HEADER* dos = (IMAGE_DOS_HEADER*)handle;
    IMAGE_NT_HEADERS* nt = (IMAGE_NT_HEADERS*)((uintptr_t)handle + dos->e_lfanew);
    
    if (!section_name) {
        region_out->base = (uintptr_t)handle;
        region_out->size = nt->OptionalHeader.SizeOfImage;
        return true;
    }

    IMAGE_SECTION_HEADER* sections = IMAGE_FIRST_SECTION(nt);
    for (int i = 0; i < nt->FileHeader.NumberOfSections; i++) {
        IMAGE_SECTION_HEADER* section = sections + i;
        if (!strcmpi((char*)section->Name, section_name)) {
            region_out->base = (uintptr_t)handle + section->VirtualAddress;
            region_out->size = section->Misc.VirtualSize;
            return true;
        }
    }
    return false;
}

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