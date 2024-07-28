#ifndef _TGA_HASHMAP
#define _TGA_HASHMAP

#include <string.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/* Simple, very crude fixed bucket size hashmap implementation */
/* TODO: replace by something better. */

typedef uint64_t(*hash_fun)(void*);
typedef bool (*eq_fun)(void*, void*);

typedef struct _hm_node
{
	struct _hm_node* next;

	void* key;
	void* value;
} hm_node;

typedef struct _hashmap
{
	hm_node** buckets;
	size_t num_buckets;

	hash_fun hash;
	eq_fun eq;

	bool free_keys; // if true, will free keys on delete
	bool free_values; // if true, will free values on delete
} hashmap;

uint64_t u64_hash(uint64_t x)
{
	x = (x ^ (x >> 30)) * 0xbf58476d1ce4e5b9ull;
	x = (x ^ (x >> 27)) * 0x94d049bb133111ebull;
	x = x ^ (x >> 31);
	return x;
}
bool u64_eq(uint64_t a, uint64_t b) { return a == b; }

uint32_t str_hash(const char* str)
{
	uint32_t hash = 5381, c;
	uint8_t* ustr = (uint8_t*)str;

	while (c = *ustr++) hash = ((hash << 5) + hash) + c;
	return hash;
}
bool str_eq(const char* a, const char* b) { return !strcmp(a, b); }

uint32_t wstr_hash(const wchar_t* str)
{
	uint32_t hash = 5381, c;
	uint8_t* ustr = (uint8_t*)str;

	while ((c = *ustr++) || *ustr) hash = ((hash << 5) + hash) + c;
	return hash;
}
bool wstr_eq(const wchar_t* a, const wchar_t* b) { return !wcscmp(a, b); }

hashmap* hm_create(size_t num_buckets, hash_fun hash, eq_fun eq, bool free_keys, bool free_values)
{
	hashmap* hm = (hashmap*)malloc(sizeof(hashmap));
	hm->buckets = (hm_node**)calloc(num_buckets, sizeof(hm_node*));
	hm->num_buckets = num_buckets;
	hm->hash = hash;
	hm->eq = eq;
	hm->free_keys = free_keys;
	hm->free_values = free_values;
	return hm;
}

hm_node* hm_set(hashmap* hm, void* key, void* value)
{
	uint64_t i = hm->hash(key) % hm->num_buckets;
	hm_node* node = hm->buckets[i];
	for (; node != NULL && !hm->eq(node->key, key); node = node->next);

	if (node == NULL)
	{
		node = (hm_node*)malloc(sizeof(hm_node));
		node->next = hm->buckets[i];
		hm->buckets[i] = node;
	}
	else
	{
		if (hm->free_keys) free(node->key);
		if (hm->free_values) free(node->value);
	}

	node->key = key;
	node->value = value;
	return node;
}

hm_node* hm_get_node(hashmap* hm, void* key)
{
	uint64_t i = hm->hash(key) % hm->num_buckets;
	hm_node* node = hm->buckets[i];
	for (; node != NULL && !hm->eq(node->key, key); node = node->next);
	return node;
}

inline void* hm_get_val(hashmap* hm, void* key)
{
	hm_node* node = hm_get_node(hm, key);
	return (node == NULL) ? NULL : node->value;
}

typedef bool (*hm_iterate_fun)(void*,void*);
void hm_iterate(hashmap* hm, hm_iterate_fun f)
{
	for (size_t i = 0; i < hm->num_buckets; i++)
	{
		if (hm->buckets[i] != NULL)
		{
			hm_node* node = hm->buckets[i];
			for (; node != NULL && !f(node->key, node->value); node = node->next);
			if (node != NULL) return;
		}
	}
}

inline bool hm_exists(hashmap* hm, void* key)
{
	return hm_get_node(hm, key) != NULL;
}

bool hm_remove(hashmap* hm, void* key)
{
	uint64_t i = hm->hash(key) % hm->num_buckets;
	hm_node* node = hm->buckets[i], * prev = NULL;
	for (; node != NULL && !hm->eq(node->key, key); node = (prev = node)->next);

	if (node != NULL)
	{
		if (hm->free_keys) free(node->key);
		if (hm->free_values) free(node->value);

		if (prev != NULL) prev->next = node->next;
		else hm->buckets[i] = node->next;

		free(node);
		return true;
	}
	else return false;
}

void hm_free(hashmap* hm)
{
	for (size_t i = 0; i < hm->num_buckets; i++)
	{
		hm_node* node = hm->buckets[i];
		if (node != NULL)
		{
			if (hm->free_keys) free(node->key);
			if (hm->free_values) free(node->value);
			free(node);
		}
	}
	free(hm->buckets);
	free(hm);
}

#endif