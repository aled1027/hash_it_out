/*
 * node.c: an implementation of a node type according to specs in node.h
 * @ifjorissen, @aled1027
 * 3.4.16
 *
*/
#include "node.h"

 /*
 Node:
   ckey_t: key 
   cval_t: val
   uint32_t: size
   node: next_node
   node: prev_node
 */
//create a new node with a key, value, and the size of the value

node_t *new_node(ckey_t key, cval_t val, uint32_t val_size){
  node_t *node = (node_t *)calloc(1, sizeof(node_t));

  node->val_size = val_size;
  
  void *keybuf = calloc(1, sizeof(*key));
  memcpy(keybuf, key, sizeof(*key));
  node->key = keybuf;

  void *valbuf = calloc(1, val_size);
  memcpy(valbuf, val, val_size);
  node->val = valbuf;

  node->next = NULL;
  node->prev = NULL;

  return node;
}

//given nodes A, B, update either A's next or prev pointer to be node B
void set_next(node_t *node, node_t *next_node){
  node->next = next_node;
}

void set_prev(node_t *node, node_t *prev_node){
  node->prev = prev_node;
}

//represent the node (print it)
void rep_node(node_t *node){
  printf("key: %d; value: %d\n", *node->key, *(uint8_t *)node->val);
}
