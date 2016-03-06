#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "cache.h"

void test_insert_same_key_twice() 
{
}

void test_mem_overflow()
{
}

void test_set_get()
{
    // TEST doesn't account for evictions!
    cache_t c = create_cache(65536, NULL);
    assert(cache_space_used(c) == 0);

    //uint32_t nsets = rand() % 50;
    uint32_t nsets = 5;
    uint8_t **saved_keys = calloc(nsets, sizeof(ckey_t));
    uint8_t *saved_vals = calloc(nsets, sizeof(uint8_t));

    for (uint32_t i = 0; i < nsets; i++) {
        uint32_t key_size = rand() % 10;
        saved_keys[i] = calloc(key_size, sizeof(uint8_t));
        for (uint32_t j = 0; j < key_size - 1; j++) {
            saved_keys[i][j] = rand() % 255;
        }
        saved_keys[i][key_size - 1] = '\0';
        saved_vals[i] = rand() % 255;
        uint32_t m = 1;
        cache_set(c, saved_keys[i], &saved_vals[i], m);
    }

    for (uint32_t i = 0; i < nsets; i++) {
        uint32_t size;
        cval_t v = cache_get(c, (ckey_t) saved_keys[i], &size);
        if (* (uint8_t *) v != saved_vals[i]) {
            assert(false && "test failed!");
        }
        free((void *) v);
    }

    destroy_cache(c);
    for (uint32_t i = 0; i < nsets; i++) {
        free(saved_keys[i]);
        saved_keys[i] = NULL;
    }
    free(saved_keys);
    free(saved_vals);
    saved_keys = NULL;
    saved_vals = NULL;
}

void test_delete_cache()
{
}

void test_collision_cache()
{
}

int main(int argc, char *argv[]) 
{
    assert(argc && argv);
    //test_cache_space();
    test_set_get();
    return 0;
}
