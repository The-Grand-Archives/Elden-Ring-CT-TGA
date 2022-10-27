#ifndef _TGA_ALIGNED_ALLOC
#define _TGA_ALIGNED_ALLOC

#include <stddef.h>

extern void* aligned_malloc(size_t size, size_t alignment);
extern void* aligned_realloc(void* ptr, size_t new_size, size_t alignment);
extern void aligned_free(void* ptr);

#endif