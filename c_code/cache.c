#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

const uint16_t MAX_ENTRIES = -1;
const bool debug = true;



uint64_t modified_jenkins(ckey_t key)
{
    // https://en.wikipedia.org/wiki/Jenkins_hash_function
    uint32_t hash = *key;
    hash += (hash << 10);
    hash ^= (hash >> 6);
    hash += (hash << 3);
    hash ^= (hash >> 11);
    hash += (hash << 15);
    return (uint64_t) hash % MAX_ENTRIES;
}
uint64_t default_hash(ckey_t k)
{
    return *k % 100;
}

typedef struct
{
    cval_t val;
    uint32_t size; // size of val in bytes
}
cache_entry;

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t memused;
    uint64_t maxmem;
    uint64_t max_entries; // TODO deal with these values
    uint64_t num_entries;

    cache_entry *entries;
    bool *is_used;
    hash_func hash;

};

cache_t create_cache(uint64_t maxmem, hash_func h) 
{
    cache_t c = calloc(1, sizeof(struct cache_obj));

    c->memused = 0;
    c->maxmem = maxmem;
    c->max_entries = MAX_ENTRIES;

    c->entries = calloc(c->max_entries, sizeof(cache_entry));
    c->is_used = calloc(c->max_entries, sizeof(bool));
    assert(c->entries && c->is_used);

    if (h == NULL) {
        //c->hash = default_hash;
        c->hash = modified_jenkins;
    } else {
        c->hash = h;
    }

    return c;
}

void cache_set(cache_t cache, ckey_t key, cval_t val, uint32_t val_size)
{

    uint64_t hash = cache->hash(key);
    if (debug) {
        printf("setting key = %" PRIu8 "\n", *key);
        printf("setting value = %" PRIu8 "\n", *(uint8_t *) val);
        printf("hash = %" PRIu64 "\n\n", hash);
    }

    if (cache->is_used[hash]) {
        cache_delete(cache, key);
    }

    cache->is_used[hash] = true;
    cache->memused += val_size;
    assert(cache->memused < cache->maxmem);

    cache_entry *e = &cache->entries[hash];
    void *memory = calloc(1, val_size); // to retain constness of e->val
    memcpy(memory, val, val_size);
    e->size = val_size;
    e->val = memory;
}

cval_t cache_get(cache_t cache, ckey_t key, uint32_t *val_size)
{
    void *ret;
    uint64_t hash = cache->hash(key);

    if (debug) {
        printf("getting key = %" PRIu8 "\n", *key);
        printf("hash = %" PRIu64 "\n\n", hash);
    }

    if (cache->is_used[hash]) {
        cache->is_used[hash] = true;
        cache_entry *e = &cache->entries[hash];
        ret = calloc(1, e->size);
        memcpy(ret, e->val, e->size);
        *val_size = e->size;
    } else {
        if (debug) {
            printf("returning null\n\n");
        }
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
    for (uint8_t i = 0; i < cache->max_entries; ++i) {
        uint64_t hash = cache->hash(&i);
        if (cache->is_used[hash]) {
            mem += cache->entries[hash].size;
        }
    }
    return mem;
}

void destroy_cache(cache_t cache)
{
    for (uint64_t i = 0; i < cache->max_entries; i++) {
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
