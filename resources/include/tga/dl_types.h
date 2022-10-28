#ifndef _TGA_DL_TYPES
#define _TGA_DL_TYPES

#include <stdint.h>

typedef struct _DLRuntimeClass {
    void** vftable_ptr;
    struct _DLRuntimeClass* base;
    void* unk02_ptr;
    void* allocator_ptr;
    char unk03_zero[24];
    char* class_name; // name of singleton base class
    wchar_t* class_name_wstr;
    char unk04_zero[8];
    uint64_t uuid;
} DLRuntimeClass;

typedef struct _DLWString
{
	union
	{
		wchar_t in_place[8];
		wchar_t* ptr;
	} str;
	uint64_t length;
	uint64_t capacity;
} DLWString;

inline const wchar_t* dlw_c_str(const DLWString* s)
{
	return (s->capacity > 7) ? s->str.ptr : s->str.in_place;
}

#endif