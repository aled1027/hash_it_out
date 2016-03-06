#include <assert.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "cache_collision.h"

void test_insert_bad_key() {
}

void test_insert_same_key() 
{
}

void test_mem_overflow()
{
}

void test_cache_space()
{
    // TEST doesn't account for evictions!
    uint8_t k, v;
    uint32_t m, mem = 0;
    cache_t c = create_cache(65536, NULL);
    assert(cache_space_used(c) == mem);
    uint32_t r = rand() % 5;
    for (uint32_t i = 0; i < r; i++) {
        k = rand() % 100;
        v = rand() % 255;
        m = rand() % 10;
        mem += m;
        cache_set(c, &k, &v, m);
        uint32_t space = cache_space_used(c);
        if (space != mem) {
            printf("test_cache_space failed\n");
            printf("i = %" PRIu32 "\n", i);
            printf("m = %" PRIu32 "\n", m);
            printf("mem = %" PRIu32 "\n", mem);
            printf("r = %" PRIu32 "\n", r);
        }
    }
}

void test_delete_cache()
{

}

void test_collision_cache()
{
    return;
}

/*
  a dummy hash function to more easily check how collisions are handled
*/
uint64_t no_hash(ckey_t key)
{
    return (uint64_t) *key;
}


void test_set_get(cache_t c){
    uint8_t *val, k, v;
    uint32_t *size = malloc(sizeof(uint32_t));

    printf("\ntesting set\n");
    k = 1;
    v = 99;
    cache_set(c, &k, &v, 1);

    k = 89;
    v = 23;
    cache_set(c, &k, &v, 2);

    k = 30;
    v = 255;
    cache_set(c, &k, &v, 1);

    k = 101;
    v = 69;
    cache_set(c, &k, &v, 1);

    printf("\ntesting get\n");

    k = 89;
    val = (uint8_t *) cache_get(c, &k, size);
    assert(*val == 23);

    k = 30;
    val = (uint8_t *) cache_get(c, &k, size);
    assert(*val == 255);

    k = 1;
    val = (uint8_t *) cache_get(c, &k, size);
    assert(*val == 99);

    k = 10;
    const char *invalid = "invalid key";
    val = (uint8_t *) cache_get(c, &k, size);
    assert(strcmp(invalid, (char *)val) == 0);

    free(size);
}

void test_destroy_cache(cache_t c){
    printf("testing....");
    destroy_cache(c);
}

int main(int argc, char *argv[]) 
{
    assert(argc && argv);
    //test_cache_space();
    printf("\ncreating cache\n");
    cache_t c = create_cache(65536, no_hash);
    test_set_get(c);
    printf("trying to destroy cache");
    test_destroy_cache(c);
    printf("...done");
    return 0;
}
