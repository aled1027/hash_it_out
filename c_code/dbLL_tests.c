#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "dbLL.h"
#include "dbLL_tests.h"

void test_dbLL_insert()
{
    printf("\n************************************************\n");
    printf("*** testing INSERTION on the doubly linked list ***\n");
    printf("************************************************\n");
    
    dbLL_t *test_ll = new_list();
    uint8_t key;
    uint8_t val;

    key = 1;
    val = 99;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 89;
    val = 23;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 12;
    val = 25;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 30;
    val = 255;
    ll_insert(test_ll, &key, &val, 1);

    //print & destroy
    rep_list(test_ll);
    destroy_list(test_ll);

    printf("*** ... done testing insertion ***\n");
    printf("************************************************\n");
}

void test_dbLL_search()
{
    printf("\n************************************************\n");
    printf("*** testing SEARCH on the doubly linked list ***\n");
    printf("************************************************\n");

    dbLL_t *test_ll = new_list();
    uint8_t key, val;
    uint8_t *res;
    uint32_t val_size;

    //setup: insert some items
    key = 1;
    val = 99;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 89;
    val = 23;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 12;
    val = 25;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 30;
    val = 255;
    ll_insert(test_ll, &key, &val, 1);

    //search for some values in the list
    key = 1;
    val = 99;
    res = (uint8_t *)ll_search(test_ll, &key, &val_size);
    assert(*res == val);

    key = 89;
    val = 23;
    res = (uint8_t *)ll_search(test_ll, &key, &val_size);
    assert(*res == val);

    key = 30;
    val = 255;
    res = (uint8_t *)ll_search(test_ll, &key, &val_size);
    assert(*res == val);

    //(try to) search for some value not in the list 
    key = 10;
    res = (uint8_t *)ll_search(test_ll, &key, &val_size);
    assert(res == NULL);

    //print & destory
    rep_list(test_ll);
    destroy_list(test_ll);

    printf("*** ... done testing search\n");
    printf("************************************************\n");
}

void test_dbLL_remove()
{
    printf("\n************************************************\n");
    printf("*** testing REMOVAL on the doubly linked list ***\n");
    printf("************************************************\n");

    dbLL_t *test_ll = new_list();
    uint8_t key;
    uint8_t val;
    uint32_t res; //actually holds the value size
    rep_list(test_ll);


    //setup: insert some items
    key = 1;
    val = 99;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 89;
    val = 23;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 12;
    val = 25;
    ll_insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 30;
    val = 255;
    ll_insert(test_ll, &key, &val, 1);

    //remove a middle value
    key = 89;
    val = 23;
    assert(val + 1 > 0); // use val to pass compiler warnings
    res = ll_remove_key(test_ll, &key);
    assert(res > 0);
    rep_list(test_ll);

    //remove the tail
    key = 30;
    val = 255;
    res = ll_remove_key(test_ll, &key);
    assert(res > 0);
    rep_list(test_ll);

    //(try to) remove a non-existent value
    key = 10;
    res = ll_remove_key(test_ll, &key);
    assert(res == 0);
    rep_list(test_ll);

    //remove the head
    key = 1;
    val = 99;
    res = ll_remove_key(test_ll, &key);
    assert(res > 0);
    rep_list(test_ll);

    //(try to) remove something we've already removed
    key = 30;
    val = 255;
    res = ll_remove_key(test_ll, &key);
    assert(res == 0);
    rep_list(test_ll);

    //remove the remaining value in the list, both the head & the tail
    key = 12;
    val = 25;
    res = ll_remove_key(test_ll, &key);
    assert(res > 0);

    //print & destory
    rep_list(test_ll);
    destroy_list(test_ll);

    printf("*** ... done testing removal\n");
    printf("************************************************\n");
}

void dbll_tests()
{
    test_dbLL_insert();
    test_dbLL_search();
    test_dbLL_remove();
}
