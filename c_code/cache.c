#include <assert.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "evict.h"
#include "dbLL.h"
#include "cache.h"

const bool debug = false;

// What is this best practice for constants? Put them at top of file or in function?
const float reset_load_factor = 0.1;
const float max_load_factor = 0.5;

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

static void print_key(ckey_t key)
{
    uint32_t i = 0;
    while (key[i]) {
        printf("%" PRIu32 ", ", key[i]);
        ++i;
    }
    printf("\n");
}

struct cache_obj 
{
    // http://stackoverflow.com/questions/6316987/should-struct-definitions-go-in-h-or-c-file
    uint64_t used_buckets;
    uint64_t num_buckets;
    uint64_t memused;
    uint64_t maxmem;
    hash_bucket **buckets; // hash_bucket is a misnomer? actually dbll_of_hbs?
    bool *is_used; // TODO not sure if being used anymore
    hash_func hash; // should only be accessed via cache_hash
    evict_t evict;

    // buckets[i] = pointer to double linked list
    // each node in double linked list is a hash-bucket
};

static uint64_t cache_hash(cache_t cache, ckey_t key) 
{
    return cache->hash(key) % cache->num_buckets;
}

static void cache_dynamic_resize(cache_t cache)
{
    // dynamically resizes size of hash table, via changing num_buckets
    // and copying key-value pairs IF the current load factor exceeds
    // the max load factor
    
    float current_load_factor = (float) cache->used_buckets / cache->num_buckets;
    if (current_load_factor > max_load_factor) {
        uint64_t new_num_buckets = (uint64_t) ((float) cache->used_buckets / reset_load_factor);

        // new memory for new cache
        hash_bucket **new_buckets = calloc(new_num_buckets, sizeof(hash_bucket*)); 
        bool *new_is_used = calloc(new_num_buckets, sizeof(bool));
        assert(new_buckets && new_is_used && "memory");
        for (uint32_t i = 0; i < new_num_buckets; i++){
            new_buckets[i] = new_list();
        }

        // loop over all possible hash values
        for (uint64_t i = 0; i < cache->num_buckets; i++) {
            if (!cache->is_used[i]) {
                continue;
            }
            hash_bucket *dbll = cache->buckets[i];
            ckey_t *keys = ll_get_keys(dbll);
            uint32_t num_keys = ll_size(dbll);
            for (uint32_t j = 0; j < num_keys; j++) {
                uint32_t val_size;
                cval_t val = ll_search(dbll, keys[j], &val_size);

                // insert key, val, val_size into dbll in new memory
                uint64_t new_hash = cache->hash(keys[j]) % new_num_buckets;
                hash_bucket *e = new_buckets[new_hash];
                ll_insert(e, keys[j], val, val_size);
                new_is_used[new_hash] = true;
                free((void *)val);
            }
            free(keys);
            destroy_list(cache->buckets[i]);
        }
        cache->num_buckets = new_num_buckets;
        free(cache->is_used);
        free(cache->buckets);
        cache->is_used = new_is_used;
        cache->buckets = new_buckets;
    } 
}

cache_t create_cache(uint64_t maxmem, hash_func h)
{
    cache_t c = calloc(1, sizeof(struct cache_obj));

    c->memused = 0;
    c->maxmem = maxmem;
    c->used_buckets = 0;
    c->num_buckets = 100;

    c->buckets = calloc(c->num_buckets, sizeof(hash_bucket*));
    assert(c->buckets);
    for (uint32_t i = 0; i < c->num_buckets; i++){
        c->buckets[i] = new_list();
    }
    c->is_used = calloc(c->num_buckets, sizeof(bool));
    assert(c->is_used);
    c->hash = (h) ? h : modified_jenkins;
    c->evict = evict_create(c->num_buckets);
    return c;
}

void cache_set(cache_t cache, ckey_t key, cval_t val, uint32_t val_size)
{

    if (debug) {
        uint64_t hash = cache_hash(cache, key);
        printf("setting key = %" PRIu8 "\n", *key);
        printf("hash = %" PRIu64 "\n", hash);
        printf("value = %" PRIu8 "\n\n", *(uint8_t *)val);
    }

    ++cache->used_buckets;
    cache_dynamic_resize(cache); // will resize cache if load factor is exceeded

    assert(cache->used_buckets < cache->num_buckets && 
            "this should never happen because of auto-balance");

    // check memory
    cache->memused += val_size;
    if (cache->memused > cache->maxmem) {
        // TODO free up memory via an eviction
    }
    uint64_t hash = cache_hash(cache, key);
    cache->is_used[hash] = true;

    // get the bucket the key belongs in, and insert it into the bucket's linked list
    hash_bucket *e = cache->buckets[hash];
    ll_insert(e, key, val, val_size);
    evict_set(cache->evict, key);
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
    evict_get(cache->evict, key);
    return res;
}

void cache_delete(cache_t cache, ckey_t key) 
{
    uint64_t hash = cache_hash(cache, key);
    uint32_t val_size;
    hash_bucket *e = cache->buckets[hash];
    val_size = ll_remove_key(e, key);
    cache->memused -= val_size;
    evict_delete(cache->evict, key);

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
        destroy_list(cache->buckets[i]);
    }

    evict_destroy(cache->evict);
    free(cache->evict);

    free(cache->buckets);
    free(cache->is_used);
    cache->buckets = NULL;
    cache->is_used = NULL;

    free(cache);
    cache = NULL;
}

void print_cache(cache_t cache)
{
    for (uint32_t i = 0; i < cache->num_buckets; ++i) {
        if (cache->is_used[i]) {
            printf("hash=%" PRIu32 " has dbll: \n", i);
            rep_list(cache->buckets[i]);
        }
    }
}
