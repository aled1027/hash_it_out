#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "dbLL.h"



dbLL_t *test_dbLL_creation(){
    printf("\n************************************************\n");
    printf("*** testing CREATION of doubly linked list ***\n");
    printf("************************************************\n");
    dbLL_t *test_ll = new_list();
    printf("\n*** ... done testing creation ***\n");
    printf("************************************************\n");
    return test_ll;
};

void test_dbLL_insert(dbLL_t *test_ll){
    printf("\n************************************************\n");
    printf("*** testing INSERTION on the doubly linked list ***\n");
    printf("************************************************\n");
    uint8_t key, val;

    key = 1;
    val = 99;
    insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 89;
    val = 23;
    insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 12;
    val = 25;
    insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    key = 30;
    val = 255;
    insert(test_ll, &key, &val, 1);
    rep_list(test_ll);

    printf("*** ... done testing insertion ***\n");
    printf("************************************************\n");
}


void test_dbLL_search(dbLL_t *test_ll){
    printf("\n************************************************\n");
    printf("*** testing SEARCH on the doubly linked list ***\n");
    printf("************************************************\n");
    uint8_t key, val;
    uint8_t *res, *exp_val;

    //search for some values in the list
    key = 1;
    val = 99;
    res = (uint8_t *)search(test_ll, &key);
    assert(*res == val);

    key = 89;
    val = 23;
    res = (uint8_t *)search(test_ll, &key);
    assert(*res == val);

    key = 30;
    val = 255;
    res = (uint8_t *)search(test_ll, &key);
    assert(*res == val);

    //(try to) search for some value not in the list 
    key = 10;
    res = (uint8_t *)search(test_ll, &key);
    assert(res == NULL);

    rep_list(test_ll);
    printf("*** ... done testing search\n");
    printf("\n************************************************\n");

};

void test_dbLL_remove(dbLL_t *test_ll){
    printf("\n************************************************\n");
    printf("*** testing REMOVAL on the doubly linked list ***\n");
    printf("************************************************\n");
    uint8_t key, val;
    uint8_t res;
    rep_list(test_ll);

    //remove a middle value
    key = 89;
    val = 23;
    res = remove_key(test_ll, &key);
    assert(res == 1);
    rep_list(test_ll);

    //remove the tail
    key = 30;
    val = 255;
    res = remove_key(test_ll, &key);
    assert(res == 1);
    rep_list(test_ll);

    //(try to) remove a non-existent value
    key = 10;
    res = remove_key(test_ll, &key);
    assert(res == 0);
    rep_list(test_ll);

    //remove the head
    key = 1;
    val = 99;
    res = remove_key(test_ll, &key);
    assert(res == 1);
    rep_list(test_ll);

    //(try to) remove something we've already removed
    key = 30;
    val = 255;
    res = remove_key(test_ll, &key);
    assert(res == 0);
    rep_list(test_ll);

    //remove the remaining value in the list, both the head & the tail
    key = 12;
    val = 25;
    res = remove_key(test_ll, &key);
    assert(res == 1);
    rep_list(test_ll);
    printf("*** ... done testing removal\n");
    printf("************************************************\n");
};

int main(int argc, char *argv[]) 
{
    assert(argc && argv);
    dbLL_t *test_ll = test_dbLL_creation();
    test_dbLL_insert(test_ll);
    test_dbLL_search(test_ll);
    test_dbLL_remove(test_ll);

    return 0;
};