/*
 * dbLL.c: a doubly linked list
 * @ifjorissen, @aled1027
 * 3.4.16
 *
*/

#include "dbLL.h"

typedef struct _dbLL_t{
  node_t *head;
  node_t *tail;
  uint32_t size;
} dbLL_t;

dbLL_t *new_list(){
  dbLL_t *list = (dbLL_t *)calloc(1, sizeof(dbLL_t));
  list->head = NULL;
  list->tail = NULL;
  list->size = 0;
  return list;
}

void insert(dbLL_t *list, ckey_t key, cval_t val, uint32_t val_size){
  node_t *node = new_node(key, val, val_size);

  if ((list->size) == 0){
    list->head = node;
    list->tail = node;
  }
  else{
    node->next = list->head;
    list->head->prev = node;
    list->head = node;
  }
  list->size += 1;
}

cval_t search(dbLL_t *list, ckey_t key){
  void *ret_val;
  node_t *cur = list->head;
  while(cur != NULL){
    if(*cur->key == *key){
      ret_val = calloc(1, cur->val_size);
      memcpy(ret_val, cur->val, cur->val_size);
      printf("a node with key: %d and value: %d was found.\n", *cur->key, *(uint8_t *)ret_val);
      return ret_val;
    }
    else{
      cur = cur->next;
    }
  }
  printf("Sorry, there wasn't anything with key: %d to find.\n", *key);
  return NULL;
}

uint8_t remove_key(dbLL_t *list, ckey_t key){
  node_t *cur = list->head;
  uint8_t removed = 0;
  while((cur != NULL) &&(removed == 0)){
    if (*cur->key == *key){
      removed = 1;
      if((cur == list->head) && (cur == list->tail)){
        printf("cur head & tail ");
        list->head = NULL;
        list->tail = NULL;
      }
      else if(cur == list->tail){
        printf("cur tail ");
        list->tail = list->tail->prev;
        list->tail->next = NULL;
      }
      else if(cur == list->head){
        printf("cur head ");
        list->head = list->head->next;
        list->head->prev = NULL;
      }
      else{
        cur->prev->next = cur->next;
        cur->next->prev = cur->prev;
      }
      printf("a node with key: %d and value: %d was found and removed.\n", *cur->key, *(uint8_t *)cur->val);
      free((void *)cur->key);
      free((void *)cur->val);
      free(cur);
      list->size -= 1;
      return removed;
    }
    else{
      cur = cur->next;
    }
  }
  if(!removed){
    printf("Sorry, there wasn't anything with key: %d to remove.\n", *key);
  }
  return removed;
}

void rep_list(dbLL_t *list){
  printf("linked list: \n\tsize: %d\n", list->size);
  node_t *cur = list->head;
  while(cur != NULL){
    printf("\t");
    rep_node(cur);
    cur = cur->next;
  }
  printf("...done printing list\n\n");
}

