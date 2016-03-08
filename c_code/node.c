/*
 * node.c: an implementation of a node type according to specs in node.h
 * @ifjorissen, @aled1027
 * 3.4.16
 *
 */
#include <stdio.h>
#include <stdint.h>
#include "node.h"

/*
Node:
ckey_t: key 
cval_t: val
uint32_t: size
node: next_node
node: prev_node
*/

node_t *new_node(ckey_t key, cval_t val, uint32_t val_size)
{
    node_t *node = (node_t *)calloc(1, sizeof(node_t));

    node->val_size = val_size;

    node->key= calloc(strlen((const char*) key) + 1, sizeof(uint8_t));
    strcpy((char *) node->key, (const char*) key);

    void *valbuf = calloc(val_size, sizeof(uint8_t));
    memcpy(valbuf, val, val_size * sizeof(uint8_t));
    node->val = valbuf;

    node->next = NULL;
    node->prev = NULL;

    return node;
}

void set_next(node_t *node, node_t *next_node)
{
    node->next = next_node;
}

void set_prev(node_t *node, node_t *prev_node)
{
    node->prev = prev_node;
}

static void print_key(ckey_t key)
{
    uint32_t i = 0;
    while (key[i]) {
        //printf("%" PRIu32 " ", key[i]);
        ++i;
    }
}
void rep_node(node_t *node)
{
    // TODO - only printing first part
    //print_key(node->key);
    printf("key: %d; value: %d\n", *node->key, *(uint8_t *)node->val);
}

ckey_t get_key(node_t *node)
{
    return node->key;
}
