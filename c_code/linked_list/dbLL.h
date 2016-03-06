/*
 * dbLL.h: headerfile for a doubly linked list
 * @ifjorissen, @aled1027
 * 3.4.16
 *
*/
#include "node.h"

typedef struct _dbLL_t dbLL_t;
struct _dbLL_t{
  node_t *head;
  node_t *tail;
  uint32_t size;
};

dbLL_t *new_list();
void ll_insert(dbLL_t *list, ckey_t key, cval_t val, uint32_t val_size);
uint32_t ll_remove_key(dbLL_t *list, ckey_t key);
cval_t ll_search(dbLL_t *list, ckey_t key);
void rep_list(dbLL_t *list);
void destroy_list(dbLL_t *list);
