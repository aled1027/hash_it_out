#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <getopt.h>

// #include "linked_list/dbLL_tests.h"
#include "cache.h"

// someone used this fancy command line argument stuff
// in a project I was working on, and I wanted to try it out
struct args {
    bool cache_tests;
    bool dbll_tests;
 };

static void args_init(struct args * args)
{
    args->cache_tests = false;
    args->dbll_tests = false;
}

static struct option opts[] =
{
    {"cache-tests", no_argument, 0, 'c'},
    {"dbll-tests", no_argument, 0, 'd'},
};

void test_mem_overflow()
{
    cache_t c = create_cache(10, NULL);
    assert(cache_space_used(c) == 0);
    uint8_t key = 10;
    uint8_t val[6] = {10,11,12,13,14,15};
    cache_set(c, &key, &val, 6);

    uint8_t key2 = 11;
    uint8_t val2[6] = {20,21,22,23,24,25};
    cache_set(c, &key2, &val2, 6);
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

void test_collision()
{
    // TODO write this someway where they don't use the same key
    // need access to the hash function
    cache_t c = create_cache(100, NULL);
    assert(cache_space_used(c) == 0);
    uint8_t key = 10;
    uint8_t val[6] = {10,11,12,13,14,15};
    cache_set(c, &key, &val, 6);

    uint8_t key2 = 10;
    uint8_t val2[4] = {20,21,22,23};
    cache_set(c, &key2, &val2, 4);
}

void test_space()
{
    cache_t c = create_cache(100, NULL);
    assert(cache_space_used(c) == 0);
    uint8_t key = 10;
    uint8_t val[6] = {10,11,12,13,14,15};
    cache_set(c, &key, &val, 6);

    uint8_t key2 = 11;
    uint8_t val2[4] = {20,21,22,23};
    cache_set(c, &key2, &val2, 4);

    assert(10 == cache_space_used(c));
}

static void cache_tests()
{
    test_mem_overflow();
    test_set_get();
    test_collision();
    test_space();
}

static int go(struct args *args)
{
    if (args->cache_tests) {
        printf("Running cache tests\n");
        cache_tests();
    }

    if (args->dbll_tests) {
        printf("Running dbll tests\n");
        // dbll_tests();
    }
    return 0;
}

int main(int argc, char *argv[]) 
{
    assert(argc && argv);

    struct args args;
    args_init(&args);

    int c, idx;
    while ((c = getopt_long(argc, argv, "", opts, &idx)) != -1) {
        switch(c) {
            case 'c':
                args.cache_tests = true;
                break;
            case 'd':
                args.dbll_tests = true;
                break;
            default:
                break;
        }
    }
    return go(&args);
}
