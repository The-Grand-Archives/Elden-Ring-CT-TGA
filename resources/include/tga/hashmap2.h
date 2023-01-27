#ifndef _TGA_HASHMAP2
#define _TGA_HASHMAP2

/* 
    hashmap2.h
    "templated" linear search hashmap using GNU C extensions
    Supports generic key and value types and dynamically grows/shrinks as needed
*/

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

#include "aligned_alloc.h"

typedef size_t hm2_hash_t;

hm2_hash_t hm2_u64_hash(uint64_t x)
{
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
	x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
	x = x ^ (x >> 31);
	return (hm2_hash_t)x;
}
bool hm2_u64_eq(uint64_t a, uint64_t b) { return a == b; }

hm2_hash_t hm2_str_hash(const char* str)
{
	uint64_t hash = 5381, c;
	uint8_t* ustr = (uint8_t*)str;

	while ((c = *ustr++)) hash = ((hash << 5) + hash) + c;
	return hash;
}
bool hm2_str_eq(const char* a, const char* b) { return !strcmp(a, b); }

hm2_hash_t hm2_wstr_hash(const wchar_t* str)
{
	uint64_t hash = 5381, c;
	uint8_t* ustr = (uint8_t*)str;

	while ((c = *ustr++) || *ustr) hash = ((hash << 5) + hash) + c;
	return hash;
}
bool hm2_wstr_eq(const wchar_t* a, const wchar_t* b) { return !wcscmp(a, b); }

hm2_hash_t hm2_default_hash(void* k, size_t size) {
    uint64_t hash = 5381;
	uint8_t* ptr = (uint8_t*)k, *end = ptr + size;

	while (ptr < end) hash = ((hash << 5) + hash) + *ptr++;
	return hash;
}

bool hm2_default_eq(void* a, void* b, size_t size) {
    return !memcmp(a, b, size);
}

// Defines hashmap with the given key and value types.
#define HASHMAP(ktype, vtype) typeof(struct { \
    size_t n_buckets; \
    size_t size; \
    \
    hm2_hash_t(*hash_fn)(ktype); \
    bool(*eq_fn)(ktype,ktype); \
    \
    ktype(*key_copy_fn)(ktype); \
    void(*key_del_fn)(ktype); \
    vtype(*val_copy_fn)(vtype); \
    void(*val_del_fn)(vtype); \
    \
    uint8_t* flags; \
    ktype* keys; \
    vtype* vals; \
})

#define HASHMAP_SIZE sizeof(HASHMAP(int, int))

#define HASHMAP_KTYPE(hm) typeof((hm)->keys[0])
#define HASHMAP_VTYPE(hm) typeof((hm)->vals[0])
#define HASHMAP_KSIZE(hm) sizeof((hm)->keys[0])
#define HASHMAP_VSIZE(hm) sizeof((hm)->vals[0])
#define HASHMAP_KALIGN(hm) __alignof__((hm)->keys[0])
#define HASHMAP_VALIGN(hm) __alignof__((hm)->vals[0])

#define HASHMAP_MIN_BUCKETS 128
#define HASHMAP_MAX_SATURATION 0.7
#define HASHMAP_GROW_FACTOR 2.0
#define HASHMAP_MIN_SATURATION 0.005

#define HM2_FREE 0
#define HM2_OCCUPIED 1
#define HM2_DELETED 2

#define HM2_IS_OCCUPIED(hm, i) ((hm)->flags[i] == HM2_OCCUPIED)
#define HM2_IS_DELETED(hm, i) ((hm)->flags[i] == HM2_DELETED)
#define HM2_IS_FREE(hm, i) ((hm)->flags[i] == HM2_FREE)
#define HM2_SET_OCCUPIED(hm, i) ((hm)->flags[i] = HM2_OCCUPIED)
#define HM2_SET_DELETED(hm, i) ((hm)->flags[i] = HM2_DELETED)
#define HM2_SET_FREE(hm, i) ((hm)->flags[i] = HM2_FREE)

// Initializes a hash map in-place, with the provided hash, equality and copy/delete functions.
#define HASHMAP_INIT(hm, hash_f, eq_f, key_copy_f, val_copy_f, key_del_f, val_del_f) { \
    (hm)->n_buckets = HASHMAP_MIN_BUCKETS; \
    (hm)->size = 0; \
    (hm)->hash_fn = hash_f; \
    (hm)->eq_fn = eq_f; \
    (hm)->key_copy_fn = key_copy_f; \
    (hm)->val_copy_fn = val_copy_f; \
    (hm)->key_del_fn = key_del_f; \
    (hm)->val_del_fn = val_del_f; \
    (hm)->flags = (uint8_t*)calloc(HASHMAP_MIN_BUCKETS, 1); \
    (hm)->keys = (HASHMAP_KTYPE(hm)*)aligned_malloc(HASHMAP_MIN_BUCKETS * HASHMAP_KSIZE(hm), HASHMAP_KALIGN(hm)); \
    (hm)->vals = (HASHMAP_VTYPE(hm)*)aligned_malloc(HASHMAP_MIN_BUCKETS * HASHMAP_VSIZE(hm), HASHMAP_VALIGN(hm)); \
    memset((hm)->keys, 0, HASHMAP_MIN_BUCKETS * HASHMAP_KSIZE(hm)); \
    memset((hm)->vals, 0, HASHMAP_MIN_BUCKETS * HASHMAP_VSIZE(hm)); \
}

// Initializes a hash map in place, with the provided hash and equality functions. Copies are done by value.
#define HASHMAP_INIT_COPY(hm, hash_f, eq_f) HASHMAP_INIT(hm, hash_f, eq_f, NULL, NULL, NULL, NULL)

// initalizes a hash map in place, with bytewise hash/equality functions and shallow value copies.
#define HASHMAP_INIT_DEFAULT(hm) HASHMAP_INIT(hm, NULL, NULL, NULL, NULL, NULL, NULL)

// Returns a pointer to a new allocated and initialized hashmap with the provided hash, equality and copy/delete functions.
#define HASHMAP_CREATE(ktype, vtype, hash_f, eq_f, key_copy_f, val_copy_f, key_del_f, val_del_f) ({ \
    HASHMAP(ktype, vtype)* hm = malloc(HASHMAP_SIZE); \
    HASHMAP_INIT(hm, hash_f, eq_f, key_copy_f, val_copy_f, key_del_f, val_del_f); \
    hm; \
})

// Returns a pointer to a new allocated and initialized hashmap with the provided hash and equality functions.
#define HASHMAP_CREATE_COPY(ktype, vtype, hash_f, eq_f) HASHMAP_CREATE(ktype, vtype, hash_f, eq_f, NULL, NULL, NULL, NULL)

// Returns a pointer to a new allocated and initialized hashmap with bytewise hash/equality functions and shallow value copies.
#define HASHMAP_CREATE_DEFAULT(ktype, vtype, hash_f, eq_f) HASHMAP_CREATE(ktype, vtype, NULL, NULL, NULL, NULL, NULL, NULL)

// Compute the hash function of the given hashmap on a key.
#define HASHMAP_HASH(hm, key_var) ((hm)->hash_fn ? (hm)->hash_fn(key_var) : hm2_default_hash(&(key_var), sizeof(key_var)))
// Compute the equality function of the given hashmap on two keys.
#define HASHMAP_EQ(hm, k1_var, k2_var) ((hm)->eq_fn ? (hm)->eq_fn(k1_var, k2_var) : hm2_default_eq(&(k1_var), &(k2_var), sizeof(k1_var)))

// Call on a value returned by HASHMAP_INSERT or HASHMAP_ERASE after you are done with it to avoid memory leaks.
#define HASHMAP_DESTROY_VALUE(hm, val) if ((hm)->val_del_fn) (hm)->val_del_fn(val)

// Finds the index of a key inside the hashmap. -1 if not found.
#define HASHMAP_FIND(hm, key_expr) ({ \
    HASHMAP_KTYPE(hm) __hmfind_key = key_expr; /* evaluate __hmfind_key */ \
    size_t i = HASHMAP_HASH(hm, __hmfind_key) % (hm)->n_buckets, j = i; \
    for (; j < (hm)->n_buckets; j++) { \
        if (HM2_IS_OCCUPIED(hm, j) && HASHMAP_EQ(hm, __hmfind_key, (hm)->vals[j])) break; \
        if (HM2_IS_FREE(hm, j)) { j = -1; break; } \
    } \
    if (j != -1 && j == (hm)->n_buckets) { \
        for (j = 0; j < i; j++) { \
            if (HM2_IS_OCCUPIED(hm, j) && HASHMAP_EQ(hm, __hmfind_key, (hm)->vals[j])) break; \
            if (HM2_IS_FREE(hm, j)) { j = -1; break; } \
        } \
        if (j == i) j = -1; \
    } \
    j; \
})

// Checks if the hashmap contains the given key.
#define HASHMAP_CONTAINS(hm, key) (HASHMAP_FIND(hm, key) != -1)
// Fetch the value at a given key in the hashmap. UB if the key does not exist.
#define HASHMAP_GET(hm, key) ((hm)->vals[HASHMAP_FIND(hm, key)])
// Returns a boolean indicating if the given key exists, and if it does writes the value to value_out.
#define HASHMAP_GET_IF_EXISTS(hm, key, value_out) ({ \
    size_t i = HASHMAP_FIND(hm, key) \
    if (i != -1) *(value_out) = (hm)->vals[i]; \
    i != -1; \
})

#define HASHMAP_RESIZE(hm, bucket_count) { \
    size_t new_n_buckets = bucket_count; /* make sure macro arg gets evaluated */ \
    uint8_t* new_flags = (uint8_t*)calloc(new_n_buckets, 1); \
    HASHMAP_KTYPE(hm)* new_keys = (HASHMAP_KTYPE(hm)*)aligned_malloc(new_n_buckets * HASHMAP_KSIZE(hm), HASHMAP_KALIGN(hm)); \
    HASHMAP_VTYPE(hm)* new_vals = (HASHMAP_VTYPE(hm)*)aligned_malloc(new_n_buckets * HASHMAP_VSIZE(hm), HASHMAP_VALIGN(hm)); \
    \
    for (size_t i = 0; i < (hm)->n_buckets; i++) { \
        if (!HM2_IS_OCCUPIED(hm, i)) continue; \
        \
        size_t j = HASHMAP_HASH(hm, (hm)->keys[i]) % (new_n_buckets), k = j; \
        for (; k < new_n_buckets && HM2_IS_OCCUPIED(hm, k); k++); \
        if (k == new_n_buckets) { \
            for (k = 0; k < j && HM2_IS_OCCUPIED(hm, k); k++); \
        } \
        \
        new_keys[k] = (hm)->keys[i]; \
        new_vals[k] = (hm)->vals[i]; \
        new_flags[k] = HM2_OCCUPIED; \
    } \
    free((hm)->flags); \
    aligned_free((hm)->keys); \
    aligned_free((hm)->vals); \
    (hm)->n_buckets = new_n_buckets; \
    (hm)->flags = new_flags; \
    (hm)->keys = new_keys; \
    (hm)->vals = new_vals; \
}

#define HASHMAP_FIND_SLOT(hm, key_expr) ({ \
    HASHMAP_KTYPE(hm) __hfindslot_key = key_expr; /* evaluate key */ \
    size_t i = HASHMAP_HASH(hm, __hfindslot_key) % (hm)->n_buckets, j = i; \
    for (; j < (hm)->n_buckets && HM2_IS_OCCUPIED(hm, j); j++); \
    if (j == (hm)->n_buckets) { \
        for (j = 0; j < i && HM2_IS_OCCUPIED(hm, j); j++); \
    } \
    j; \
})

// Tries to insert given (key, value) pair in the hashmap, returning true if a value was already present at key. 
// Optionally writes the old value, if any, to prev_out_opt. If prev_out_opt is null, the old value will be deleted via hm->val_del_fn.
#define HASHMAP_INSERT(hm, key_expr, val_expr, prev_out_opt) ({ \
    HASHMAP_KTYPE(hm) __hinsert_key = key_expr; /* evaluate args */ \
    HASHMAP_VTYPE(hm) __hinsert_val = val_expr, *__hinsert_out = prev_out_opt; \
    \
    size_t i = HASHMAP_FIND(hm, __hinsert_key); \
    if (i != -1) { \
        if (__hinsert_out) *__hinsert_out = (hm)->vals[i]; \
        else if ((hm)->val_del_fn) (hm)->val_del_fn((hm)->vals[i]); \
        (hm)->vals[i] = (hm)->val_copy_fn ? (hm)->val_copy_fn(__hinsert_val) : __hinsert_val; \
    } else { \
        if ((hm)->size > (size_t)((double)((hm)->n_buckets) * HASHMAP_MAX_SATURATION)) { \
            HASHMAP_RESIZE(hm, (size_t)((double)((hm)->n_buckets) * HASHMAP_GROW_FACTOR)); \
        } \
        size_t j = HASHMAP_FIND_SLOT(hm, __hinsert_key); \
        (hm)->keys[j] = (hm)->key_copy_fn ? (hm)->key_copy_fn(__hinsert_key) : __hinsert_key; \
        (hm)->vals[j] = (hm)->val_copy_fn ? (hm)->val_copy_fn(__hinsert_val) : __hinsert_val; \
        HM2_SET_OCCUPIED(hm, j); \
        (hm)->size++; \
    } \
    i != -1; \
})

// Tries to erase an item given its key, returning true if the item was present. 
// Optionally writes value, if any, to val_out_opt. If val_out_opt is null, the old value will be deleted via hm->val_del_fn.
#define HASHMAP_ERASE(hm, key_expr, val_out_opt) ({ \
    HASHMAP_KTYPE(hm) __herase_key= key_expr; /* evaluate args */ \
    HASHMAP_VTYPE(hm)* __herase_out = val_out_opt; \
    \
    size_t i = HASHMAP_FIND(hm, __herase_key); \
    if (i != -1) { \
        if ((hm)->key_del_fn) (hm)->key_del_fn((hm)->keys[i]); \
        if (__herase_out) *__herase_out = (hm)->vals[i]; \
        else if ((hm)->val_del_fn) (hm)->val_del_fn((hm)->vals[i]); \
        HM2_SET_DELETED(hm, i); \
        size_t min_size = (size_t)((double)((hm)->n_buckets) * HASHMAP_MIN_SATURATION); \
        if ((hm)->size-- < min_size) { \
            size_t new_n_buckets = (size_t)((double)((hm)->size) * HASHMAP_GROW_FACTOR / HASHMAP_MAX_SATURATION); \
            if (new_n_buckets < HASHMAP_MIN_BUCKETS) new_n_buckets = HASHMAP_MIN_BUCKETS; \
            if ((hm)->n_buckets > new_n_buckets) { \
                HASHMAP_RESIZE(hm, new_n_buckets); \
            } \
        } \
    } \
    i != -1; \
})

#define HASHMAP_CLEAR(hm) { \
    /* run deleter on keys and values, if any */ \
    if ((hm)->key_del_fn || (hm)->val_del_fn) { \
        for (size_t i = 0; i < (hm)->n_buckets; i++) { \
            if (HM2_IS_OCCUPIED(hm, i)) { \
                if ((hm)->key_del_fn) (hm)->key_del_fn((hm)->keys[i]); \
                if ((hm)->val_del_fn) (hm)->val_del_fn((hm)->vals[i]); \
            } \
        } \
    } \
    /* resize to default min capacity */ \
    (hm)->n_buckets = HASHMAP_MIN_BUCKETS; \
    (hm)->size = 0; \
    (hm)->flags = realloc((hm)->flags, HASHMAP_MIN_BUCKETS); \
    memset((hm)->flags, 0, HASHMAP_MIN_BUCKETS); \
    (hm)->keys = aligned_realloc((hm)->keys, HASHMAP_MIN_BUCKETS * HASHMAP_KSIZE(hm), HASHMAP_KALIGN(hm)); \
    (hm)->vals = aligned_realloc((hm)->vals, HASHMAP_MIN_BUCKETS * HASHMAP_VSIZE(hm), HASHMAP_VALIGN(hm)); \
}

// Deletes (frees) an allocated hashmap created using HASHMAP_CREATE.
#define HASHMAP_DELETE(hm) { \
    HASHMAP_CLEAR(hm); \
    free((hm)->flags); \
    aligned_free((hm)->keys); \
    aligned_free((hm)->vals); \
    free(hm); \
}

#endif