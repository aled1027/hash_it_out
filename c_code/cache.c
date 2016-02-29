#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

uint64_t default_cache(ckey_t k)
{
    return *k % 100;
}

typedef struct
{
    cval_t val;
    uint32_t size; // size of val in bytes
} cache_entry;

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t size;
    cache_entry *entries;
    bool *is_used;
    hash_func hash;

};

cache_t create_cache(uint64_t maxmem, hash_func h) 
{
    cache_t c = calloc(1, sizeof(struct cache_obj));
    c->size = maxmem;
    c->entries = calloc(maxmem, sizeof(cache_entry));
    c->is_used = calloc(maxmem, sizeof(bool));

    if (h == NULL) {
        c->hash = default_cache;
    } else {
        c->hash = h;
    }

    return c;
}

void cache_set(cache_t cache, ckey_t key, cval_t val, uint32_t val_size)
{
    uint64_t hash = cache->hash(key);
    assert(hash < cache->size && "won't be able to access that memory");

    if (cache->is_used[hash]) {
        cache_delete(cache, key);
    }
    cache->is_used[hash] = true;
    cache_entry *e = &cache->entries[hash];


    // do this kind of strange thing to retain constness of cval_t
    void *memory = calloc(1, val_size);
    memcpy(memory, val, val_size);

    e->size = val_size;
    e->val = memory;
}

cval_t cache_get(cache_t cache, ckey_t key, uint32_t *val_size)
{
    void *ret;
    uint64_t hash = cache->hash(key);
    if (cache->is_used[hash]) {
        cache->is_used[hash] = true;
        cache_entry *e = &cache->entries[hash];
        ret = calloc(1, e->size);
        memcpy(ret, e->val, e->size);
        *val_size = e->size;
    } else {
        ret = NULL;
    }
    return ret;
}

void cache_delete(cache_t cache, ckey_t key) 
{
    uint64_t hash = cache->hash(key);
    cache->is_used[hash] = false;
    free((void *) cache->entries[hash].val); // TODO don't need to do this - use realloc
}

uint64_t cache_space_used(cache_t cache)
{
    uint64_t mem = 0;
    for (uint8_t i = 0; i < cache->size; ++i) {
        uint64_t hash = cache->hash(&i);
        if (cache->is_used[hash]) {
            mem += cache->entries[hash].size;
        }
    }
    return mem;
}

void destroy_cache(cache_t cache)
{
    for (uint64_t i = 0; i < cache->size; i++) {
        free((void *) cache->entries[i].val);
        cache->entries[i].val = NULL;
    }
    free(cache->entries);
    cache->entries = NULL;
    free(cache->is_used);
    cache->is_used = NULL;
    free(cache);
    cache = NULL;
} 
