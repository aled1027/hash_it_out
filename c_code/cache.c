#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "cache.h"

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
    return (uint64_t) hash;
}


typedef struct
{
    ckey_t key;
    cval_t val;
    uint32_t size; // size of val in bytes
}
hash_bucket;

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t used_buckets;
    uint64_t num_buckets;
    uint64_t memused;
    uint64_t maxmem;

    hash_bucket *buckets;
    bool *is_used;
    hash_func hash; // should only be accessed via cache_hash
};

static uint64_t cache_hash(cache_t cache, ckey_t key) 
{
    return cache->hash(key) % cache->num_buckets;
}

cache_t create_cache(uint64_t maxmem, hash_func h) 
{
    cache_t c = calloc(1, sizeof(struct cache_obj));

    c->memused = 0;
    c->maxmem = maxmem;
    c->used_buckets = 0;
    c->num_buckets = 100; //

    c->buckets = calloc(c->num_buckets, sizeof(hash_bucket));
    c->is_used = calloc(c->num_buckets, sizeof(bool));
    assert(c->buckets && c->is_used);

    if (h == NULL) {
        c->hash = modified_jenkins;
    } else {
        c->hash = h;
    }

    return c;
}

void cache_set(cache_t cache, ckey_t key, cval_t val, uint32_t val_size)
{

    uint64_t hash = cache_hash(cache, key);

    if (debug) {
        printf("setting key = %" PRIu8 "\n", *key);
        printf("hash = %" PRIu64 "\n", hash);
        printf("value = %" PRIu8 "\n\n", *(uint8_t *)val);
    }

    ++cache->used_buckets;
    // TODO
    // if (condition for rebalancing):
    //      cache_rebalance(cache);
    

    assert(cache->used_buckets < cache->num_buckets && "this should never happen because of auto-balance");
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
    hash_bucket *e = &cache->buckets[hash];
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
    uint64_t hash = cache_hash(cache, key);

    if (debug) {
        printf("getting key = %" PRIu8 "\n", *key);
        printf("hash = %" PRIu64 "\n\n", hash);
    }

    if (cache->is_used[hash]) {
        hash_bucket *e = &cache->buckets[hash];
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
    uint64_t hash = cache_hash(cache, key);
    if (cache->is_used) {
        --cache->num_buckets;
        cache->memused -= cache->buckets[hash].size;
        cache->is_used[hash] = false;
        free((void *) cache->buckets[hash].val); 
        free((void *) cache->buckets[hash].key);
        cache->buckets[hash].val = NULL;
        cache->buckets[hash].key = NULL;
        cache->buckets[hash].size = 0;
    }

}

uint64_t cache_space_used(cache_t cache)
{
    return cache->memused;
}

void destroy_cache(cache_t cache)
{
    for (uint64_t i = 0; i < cache->num_buckets; i++) {
        uint64_t hash = cache_hash(cache, (ckey_t) &i);
        cache_delete(cache, (ckey_t) &i);
    }

    free(cache->buckets);
    free(cache->is_used);
    cache->buckets = NULL;
    cache->is_used = NULL;

    free(cache);
    cache = NULL;
} 
