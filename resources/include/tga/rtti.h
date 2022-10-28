#ifndef _TGA_RTTI_H
#define _TGA_RTTI_H

#include <stdint.h>
#include <stdbool.h>
#include <string.h>

#include "win_extra.h"
#include "mem_region.h"

typedef struct _PMD {
    int32_t mdisp;
    int32_t pdisp;
    int32_t vdisp;
} PMD;

typedef struct _RTTITypeDescriptor {
    void** pVFTable; // NOTE: NOT the class vtable (points to type_info::vftable)
    void* spare; // Typically NULL
    const char name[0];
} RTTITypeDescriptor;

typedef struct _RTTIBaseClassDescriptor {
    ibo32 pTypeDescriptor;
    uint32_t numContainedBases;
    PMD where;
    uint32_t attributes;
    ibo32 pClassHierarchy;
} RTTIBaseClassDescriptor;

typedef struct _RTTIBaseClassArray {
    ibo32 arrayOfBaseClassDescriptors[1];
} RTTIBaseClassArray;

typedef struct _RTTIClassHierarchyDescriptor {
    uint32_t signature; // 0 = x86, 1 = x64
    uint32_t attributes; // 1 => multiple inheritance, 2 => virtual inheritance
    uint32_t numBaseClasses;
    ibo32 pBaseClassArray;
} RTTIClassHierarchyDescriptor;

typedef struct _RTTICompleteObjectLocator {
    uint32_t signature; // 0 = x86, 1 = x64
    uint32_t offset;
    uint32_t cdOffset;
    ibo32 pTypeDescriptor;
    ibo32 pClassDescriptor;
    ibo32 pSelf; // Only in x64, points to the start of this struct
} RTTICompleteObjectLocator;

// Tries to find the demangled name of the class a suspected vtable belongs to. Returns FALSE
// if the RTTI data could not be found/parsed.
bool get_rtti_class_name_vmt(const region* mod, void** vtable, char* out_name, size_t out_name_cb) {
    if (!ptr_in_region(vtable - 1, mod)) return false;

    const RTTICompleteObjectLocator* locator = *(RTTICompleteObjectLocator**)(vtable - 1);
    if (!ptr_in_region(locator, mod)) return false;

    if (locator->signature != 1) return false;
    if (ibo32_get_ptr(locator->pSelf, mod) != (uintptr_t)locator) return false;

    const RTTITypeDescriptor* descriptor = (const RTTITypeDescriptor*)ibo32_get_ptr(locator->pTypeDescriptor, mod);
    if (!ptr_in_region(descriptor, mod)) return false;
    if (!ptr_in_region(descriptor->pVFTable, mod)) return false;
    if (strncmp(descriptor->name, ".?", 2)) return false;

    // 14338 = UNDNAME_32_BIT_DECODE | UNDNAME_NAME_ONLY | UNDNAME_NO_ARGUMENTS | UNDNAME_NO_MS_KEYWORDS
    if (!UnDecorateSymbolName(descriptor->name + 1, out_name, out_name_cb, 14338))
        return false;

    return true;
}

// Tries to find the demangled name of the class a an object belongs to. Returns FALSE
// if the RTTI data could not be found/parsed.
bool get_rtti_class_name(const region* mod, void* obj, char* out_name, size_t out_name_cb)
{
    void** vtable = *(void***)obj;
    return get_rtti_class_name_vmt(mod, vtable, out_name, out_name_cb);
}

#endif