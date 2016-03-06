#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbLL.h"
#include "cache.h"

const bool debug = false;

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

typedef struct _dbLL_t hash_bucket;

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t used_buckets;
    uint64_t num_buckets;
    uint64_t memused;
    uint64_t maxmem;

    hash_bucket **buckets;
    bool *is_used;
    hash_func hash; // should only be accessed via cache_hash

    // buckets[i] holds a pointer to a double linked list
    // in the double linked list, nodes in the double linked list
    // are hash buckets
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
    c->num_buckets = 1000;

    c->buckets = calloc(c->num_buckets, sizeof(hash_bucket*));
    assert(c->buckets);
    for (uint32_t i = 0; i < c->num_buckets; i++){
        c->buckets[i] = new_list();
    }
    c->is_used = calloc(c->num_buckets, sizeof(bool));
    assert(c->is_used);
    c->hash = (h) ? h : modified_jenkins;
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
    

    assert(cache->used_buckets < cache->num_buckets && 
            "this should never happen because of auto-balance");

    // check memory
    cache->memused += val_size;
    if (cache->memused > cache->maxmem) {
        // TODO free up memory via an eviction
    }
    cache->is_used[hash] = true;

    // get the bucket the key belongs in, and insert it into the bucket's linked list
    hash_bucket *e = cache->buckets[hash];
    ll_insert(e, key, val, val_size);
}

cval_t cache_get(cache_t cache, ckey_t key, uint32_t *val_size)
{
    uint64_t hash = cache_hash(cache, key);

    if (debug) {
        printf("getting key = %" PRIu8 "\n", *key);
        printf("hash = %" PRIu64 "\n\n", hash);
    }

    hash_bucket *e = cache->buckets[hash];
    void *res = (void *) ll_search(e, key, val_size);
    return res;
}

void cache_delete(cache_t cache, ckey_t key) 
{
    uint64_t hash = cache_hash(cache, key);
    uint32_t val_size;
    hash_bucket *e = cache->buckets[hash];
    val_size = ll_remove_key(e, key);
    cache->memused -= val_size;

    if (e->size == 0) {
        cache->is_used[hash] = false;
        --cache->used_buckets;
    }
}

uint64_t cache_space_used(cache_t cache)
{
    return cache->memused;
}

void destroy_cache(cache_t cache)
{
    for (uint64_t i = 0; i < cache->num_buckets; i++) {
        if (cache->buckets[i]->size != 0) {
            destroy_list(cache->buckets[i]);
        }
    }

    free(cache->buckets);
    free(cache->is_used);
    cache->buckets = NULL;
    cache->is_used = NULL;

    free(cache);
    cache = NULL;
}
