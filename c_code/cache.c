#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

const uint64_t MAX_ENTRIES = 65535;
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
    ckey_t key;
    cval_t val;
    uint32_t size; // size of val in bytes
}
cache_entry;

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t num_entries;
    uint64_t max_entries; 
    uint64_t memused;
    uint64_t maxmem;

    cache_entry *entries;
    bool *is_used;
    hash_func hash;
};

cache_t create_cache(uint64_t maxmem, hash_func h) 
{
    cache_t c = calloc(1, sizeof(struct cache_obj));

    c->memused = 0;
    c->maxmem = maxmem;
    c->num_entries = 0;
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

    printf("getting key = %" PRIu8 "\n", *key);
    printf("hash = %" PRIu64 "\n\n", hash);

    ++cache->num_entries;
    assert(cache->num_entries < cache->max_entries && "this should never happen");

    // check memory
    cache->memused += val_size;
    if (cache->memused > cache->maxmem) {
        // TODO free up memory via an eviction
    }

    // check for collision
    if (cache->is_used[hash]) {
        // TODO collision
        cache_delete(cache, key);
    }

    cache->is_used[hash] = true;

    // add the value
    cache_entry *e = &cache->entries[hash];
    e->size = val_size;

    void *key_buf = calloc(1, sizeof(*key));
    memcpy(key_buf, key, sizeof(*key));
    e->key = key_buf;

    void *val_buf = calloc(1, val_size); // to retain constness of e->val
    memcpy(val_buf, val, val_size);
    e->val = val_buf;
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
        cache_entry *e = &cache->entries[hash];
        if (*e->key == *key) {
            ret = calloc(1, e->size);
            memcpy(ret, e->val, e->size);
            *val_size = e->size;
        } else {
            // COLLISION TODO
        }

    } else {
        ret = NULL;
    }
    return ret;
}

void cache_delete(cache_t cache, ckey_t key) 
{
    uint64_t hash = cache->hash(key);
    if (cache->is_used) {
        --cache->num_entries;
        cache->memused -= cache->entries[hash].size;
        cache->is_used[hash] = false;
        free((void *) cache->entries[hash].val); 
        free((void *) cache->entries[hash].key);
        cache->entries[hash].val = NULL;
        cache->entries[hash].key = NULL;
        cache->entries[hash].size = 0;
    }

}

uint64_t cache_space_used(cache_t cache)
{
    return cache->memused;
}

void destroy_cache(cache_t cache)
{
    for (uint64_t i = 0; i < cache->max_entries; i++) {
        cache_delete(cache, (ckey_t) &i);
    }

    free(cache->entries);
    free(cache->is_used);
    cache->entries = NULL;
    cache->is_used = NULL;

    free(cache);
    cache = NULL;
} 
