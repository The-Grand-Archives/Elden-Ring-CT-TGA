#ifndef _TGA_VECTOR
#define _TGA_VECTOR

/* 
    vector.h
    Macro-based "templated" dynamic size array type, similar to a C++ vector<T>.
*/

#include "aligned_alloc.h"
#include <stdlib.h>
#include <string.h>

#define VECTOR_MIN_CAPACITY 32 // minimum capacity of a vector

// Defines a vector type 
#define VECTOR(type) typeof(struct { \
    type* data; \
    size_t size; \
    size_t capacity; \
    type(*copy_fn)(type); \
    void(*del_fn)(type); \
})

// Size of a vector struct (invariant of type)
#define VECTOR_SIZE sizeof(VECTOR(int))

// Get the size of a vector element
#define VECTOR_ELEM_SIZE(vec) sizeof((vec)->data[0])

// Get the alignment of a vector element
#define VECTOR_ALIGN_OF(vec) __alignof__((vec)->data[0])

// Get the type of element this vector contains
#define VECTOR_TYPE(vec) typeof((vec)->data[0])

// Invoke the custom element copy function on elem, if it is defined. 
#define VECTOR_ELEM_COPY(vec, elem) ((vec)->copy_fn ? (vec)->copy_fn(elem) : elem)

// Invoke the custom element delete function on elem, if it is defined.
#define VECTOR_ELEM_DEL(vec, elem) if ((vec)->del_fn) (vec)->del_fn(elem)

// Initializes a vector struct with the given element copy/delete functions.
// These can be made NULL if value copy of element type is enough. 
#define VECTOR_INIT(vec, copy_f, del_f) { \
    (vec)->data = aligned_malloc(VECTOR_ELEM_SIZE(vec) * VECTOR_MIN_CAPACITY, VECTOR_ALIGN_OF(vec)); \
    (vec)->size = 0; \
    (vec)->capacity = VECTOR_MIN_CAPACITY; \
    (vec)->copy_fn = copy_f; \
    (vec)->del_fn = del_f; \
}

// Allocates a new empty vector with the given element copy/delete functions, and returns a pointer to it.
#define VECTOR_CREATE(type, copy_f, del_f) ({ \
    VECTOR(type)* vec = malloc(VECTOR_SIZE); \
    VECTOR_INIT(vec, copy_f, del_f); \
    vec; \
})

// Grows a vector's capacity if it's full.
#define VECTOR_GROW_IF_REQUIRED(vec) { \
    if ((vec)->size == (vec)->capacity) { \
        (vec)->capacity <<= 1; \
        (vec)->data = (typeof((vec)->data))aligned_realloc((vec)->data, (vec)->capacity * VECTOR_ELEM_SIZE(vec), VECTOR_ALIGN_OF(vec)); \
    } \
}

// Shrinks the vector's capacity if the size is significantly smaller.
#define VECTOR_SHRINK_IF_REQUIRED(vec) { \
    size_t __vsrhink_threshold = (vec)->size << 2; \
    if (__vsrhink_threshold < VECTOR_MIN_CAPACITY) __vsrhink_threshold = VECTOR_MIN_CAPACITY; \
    else if (__vsrhink_threshold < (vec)->capacity) { \
        while (__vsrhink_threshold < (vec)->capacity) (vec)->capacity >>= 1; \
        (vec)->data = (typeof((vec)->data))aligned_realloc((vec)->data, (vec)->capacity * VECTOR_ELEM_SIZE(vec), VECTOR_ALIGN_OF(vec)); \
    } \
}

// Pushes an element on the vector. Returns the index of the element.
#define VECTOR_PUSH(vec, elem) ({ \
    VECTOR_GROW_IF_REQUIRED(vec); \
    (vec)->data[(vec)->size] = VECTOR_ELEM_COPY(vec, elem); \
    (vec)->size++; \
})

// Replaces the element at the given index inside the vector. UB if index out of bounds.
#define VECTOR_SET_AT(vec, index, elem) { \
    VECTOR_ELEM_DEL(vec, (vec)->data[index]); \
    (vec)->data[index] = VECTOR_ELEM_COPY(vec, elem); \
}

// Inserts an element at a given index inside the vector. 
// Index can be equal to the size; in this case, the element is added to the end.
#define VECTOR_INSERT_AT(vec, index, elem) { \
    VECTOR_GROW_IF_REQUIRED(vec); \
    memmove((vec)->data + index + 1, (vec)->data + index, ((vec)->size++ - index) * VECTOR_ELEM_SIZE(vec)); \
    (vec)->data[index] = VECTOR_ELEM_COPY(vec, elem); \
}

// Removes the last element of the vector. Returns its value.
// Be sure to call VECTOR_ELEM_DEL (or the deleter directly if you know it) on the return value after use,
// to avoid memory leaks.
#define VECTOR_POP(vec) ({ \
    VECTOR_TYPE(vec) __vpop_elem = (vec)->data[--((vec)->size)]; \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    __vpop_elem; \
})

// Removes the last element of the vector and deletes it.
#define VECTOR_POP_DELETE(vec) VECTOR_ELEM_DEL(vec, VECTOR_POP(vec))

// Pops an element at a given index, returning the value that was removed.
// Be sure to call VECTOR_ELEM_DEL (or the deleter directly if you know it) on the return value after use,
// to avoid memory leaks.
#define VECTOR_POP_AT(vec, index) ({ \
    VECTOR_TYPE(vec) __vpop_at_elem = (vec)->data[index]; \
    memmove((vec)->data + index, (vec)->data + index + 1, (--((vec)->size) - index) * VECTOR_ELEM_SIZE(vec)); \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    __vpop_at_elem; \
})

// Removes the element at a given index of the vector and deletes it.
#define VECTOR_REMOVE_AT(vec, index) VECTOR_ELEM_DEL(vec, VECTOR_POP_AT(vec, index))

// Removes all elements for which the given predicate returns "true". The predicate is an expression scope given two variables:
// - Index "i"
// - Pointer to element "elem"
// Returns the number of elements removed.
#define VECTOR_REMOVE_IF(vec, predicate) ({ \
    size_t __vremif_n_removed = 0; \
    for (size_t i = 0; i < (vec)->size; i++) { \
        typeof((vec)->data) elem = (vec)->data + i; \
        if ((predicate)) { \
            VECTOR_ELEM_DEL(vec, *elem); \
            __vremif_n_removed++; \
        } \
        else if (__vremif_n_removed > 0) { \
            (vec)->data[i - __vremif_n_removed] = (vec)->data[i]; \
        } \
    } \
    (vec)->size -= __vremif_n_removed; \
    VECTOR_SHRINK_IF_REQUIRED(vec); \
    __vremif_n_removed; \
})

// Returns the index of first element in the vector for which the predicate returns "true". 
// If the element is not found, returns -1. The predicate is an expression scope given two variables:
// - Index "i"
// - Pointer to element "elem"
#define VECTOR_FIND(vec, predicate) ({ \
    size_t i = 0; \
    for (; i < (vec)->size; i++) { \
        typeof((vec)->data) elem = (vec)->data + i; \
        if ((predicate)) break; \
    } \
    if (i == (vec)->size) i = -1; \
    i; \
})

// Returns the index of first element in the vector for which the predicate returns "true", 
// starting from the end. If the element is not found, returns -1. The predicate is an expression scope given two variables:
// - Index "i"
// - Pointer to element "elem"
#define VECTOR_RFIND(vec, predicate) ({ \
    size_t i = (vec)->size - 1; \
    for (; i >= 0; i--) { \
        typeof((vec)->data) elem = (vec)->data + i; \
        if ((predicate)) break; \
    } \
    i; \
})

// Removes all values inside the vector.
#define VECTOR_CLEAR(vec) { \
    if ((vec)->del_fn) { \
        for (size_t i = 0; i < (vec)->size; i++) \
            (vec)->del_fn((vec)->data[i]); \
    } \
    (vec)->data = aligned_realloc((vec)->data, VECTOR_ELEM_SIZE(vec) * VECTOR_MIN_CAPACITY, VECTOR_ALIGN_OF(vec)); \
    (vec)->size = 0; \
    (vec)->capacity = VECTOR_MIN_CAPACITY; \
}

// Frees a dynamically allocated vector created with VECTOR_CREATE. 
#define VECTOR_DELETE(vec) { \
    VECTOR_CLEAR(vec); \
    free(vec); \
}

#endif