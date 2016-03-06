/*
 * node.h: the header file for a node
 * @ifjorissen, @aled1027
 * 3.4.16
 *
*/

#ifndef _NODE_H
#define _NODE_H
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../cache.h"

// struct _node_t;
typedef struct _node_t node_t;
struct _node_t
 {
   ckey_t key;
   cval_t val;
   uint32_t val_size;
   node_t *next;
   node_t *prev;
 };


//create a new node with a key, value, and the size of the value
node_t *new_node(ckey_t key, cval_t val, uint32_t val_size);

//given nodes A, B, update either A's next or prev pointer to be node B
void set_next(node_t *node, node_t *next);
void set_prev(node_t *node, node_t *prev);

//represent the node (print it)
void rep_node(node_t *node); 

#endif
