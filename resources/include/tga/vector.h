#ifndef _TGA_VECTOR
#define _TGA_VECTOR

/* vector.h
Macro-based dynamic size array type, similar to a C++ vector<T>.
*/

#include "aligned_alloc.h"
#include <string.h>

#define VECTOR_MIN_CAPACITY 32 // minimum capacity of a vector

// Defines a vector type 
#define VECTOR(type) typeof(struct { type* data; size_t size; size_t capacity; })

// Get the size of a vector element
#define VECTOR_ELEM_SIZE(vec) sizeof(vec->data[0])

// Get the alignment of a vector element
#define VECTOR_ALIGN_OF(vec) __alignof__(vec->data[0])

// Get the type of element this vector contains
#define VECTOR_TYPE(vec) typeof(vec->data[0])

// Creates a new vector with variable name "vec" and type "type".
#define VECTOR_NEW(vec, type) VECTOR(type) vec = { \
    .data = aligned_malloc(sizeof(type) * VECTOR_MIN_CAPACITY, __alignof__(type)), \
    .size = 0, \
    .capacity = VECTOR_MIN_CAPACITY \
}

// Grows a vector's capacity if it's full.
#define VECTOR_GROW_IF_REQUIRED(vec) { \
    if (vec->size == vec->capacity) { \
        vec->capacity <<= 1; \
        vec->data = (typeof(vec->data))aligned_realloc(vec->data, vec->capacity * VECTOR_ELEM_SIZE(vec), VECTOR_ALIGN_OF(vec)); \
    } \
}

// Shrinks the vector's capacity if the size is significantly smaller.
#define VECTOR_SHRINK_IF_REQUIRED(vec) { \
    size_t threshold = vec->size << 2; \
    if (threshold < VECTOR_MIN_CAPACITY) threshold = VECTOR_MIN_CAPACITY; \
    else if (treshold < vec->capacity) { \
        while (theshold < vec->capacity) vec->capacity >>= 1; \
        vec->data = (typeof(vec->data))aligned_realloc(vec->data, vec->capacity * VECTOR_ELEM_SIZE(vec), VECTOR_ALIGN_OF(vec)); \
    } \
}

// Pushes an element on the vector. Returns the index of the element.
#define VECTOR_PUSH(vec, elem) ({ \
    VECTOR_GROW_IF_REQUIRED(vec); \
    vec->data[vec->size] = elem; \
    size++; \
})

// Inserts an element at a given index inside the vector. 
// Index can be equal to the size; in this case, the element is added to the end.
#define VECTOR_INSERT_AT(vec, elem, index) { \
    VECTOR_GROW_IF_REQUIRED(vec); \
    memmove(vec->data + index + 1, vec->data + index, (vec->size++ - index) * VECTOR_ELEM_SIZE(vec)); \
    vec->data[index] = elem; \
}

// Removes the last element of the vector. Returns its value.
#define VECTOR_POP(vec) ({ \
    VECTOR_TYPE(vec) elem = vec->data[--vec->size]; \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    elem; \
})

// Removes an element at given index. Returns the value that was removed.
#define VECTOR_REMOVE_AT(vec, index) ({ \
    VECTOR_TYPE(vec) elem = vec->data[index]; \
    memmove(vec->data + index, vec->data + index + 1, (--vec->size - index) * VECTOR_ELEM_SIZE(vec)); \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    elem; \
})

// Removes all elements for which the given predicate returns "true". The predicate is given two variables:
// - Index "i"
// - Pointer to element "elem"
// Returns the number of elements removed.
#define VECTOR_REMOVE_IF(vec, predicate) ({ \
    size_t num_removed = 0; \
    for (size_t i = 0; i < vec->size; i++) { \
        typeof(vec->data) elem = vec->data + i; \
        if ((predicate)) { \
            num_removed++; \
        } \
        else if (num_removed > 0) { \
            vec->data[i - num_removed] = vec->data[i]; \
        } \
    } \
    vec->size -= num_removed; \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    num_removed; \
})

// Returns the inex of first element in the vecotr for which the predicate returns "true". 
// If the element is not found, returns -1. The predicate is given two variables:
// - Index "i"
// - Pointer to element "elem"
#define VECTOR_FIND(vec, predicate) ({ \
    size_t i = 0; \
    for (; i < vec->size; i++) { \
        typeof(vec->data) elem = vec->data + i; \
        if ((predicate)) break; \
    } \
    if (i == vec->size) i = -1; \
    i; \
})

// Returns the inex of first element in the vecotr for which the predicate returns "true", 
// starting from the end. If the element is not found, returns -1. The predicate is given two variables:
// - Index "i"
// - Pointer to element "elem"
#define VECTOR_RFIND(vec, predicate) ({ \
    size_t i = vec->size - 1; \
    for (; i >= 0; i--) { \
        typeof(vec->data) elem = vec->data + i; \
        if ((predicate)) break; \
    } \
    i; \
})

#endif