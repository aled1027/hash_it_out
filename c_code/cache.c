#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

#include "cache.h"

//typedef uint64_t (*hash_func)(ckey_t key);

cache_t create_cache(uint64_t maxmem) {
    cache_t c = malloc(maxmem);
    return c;
}

void cache_set(cache_t cache, ckey_t key, cval_t *val)
{
    assert(cache && key && val);
    return;
}

cval_t cache_get(cache_t cache, ckey_t key)
{
    assert(cache && key);
    return 0;
}

void cache_delete(cache_t cache, ckey_t key) 
{
    assert(cache && key);
    return;
}

uint64_t cache_space_used(cache_t cache)
{
    assert(cache);
    return 0;
}

void destroy_cache(cache_t cache)
{
    assert(cache);
    return;
}

void print_cache(cache_t cache) 
{
    assert(cache);
    return;
}
