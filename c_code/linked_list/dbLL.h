/*
 * dbLL.h: headerfile for a doubly linked list
 * @ifjorissen, @aled1027
 * 3.4.16
 *
*/
#include "node.h"

struct _dbLL_t;
typedef struct _dbLL_t dbLL_t;

dbLL_t *new_list();

// insert a new node into the list with (key, val, val_size)
void insert(dbLL_t *list, ckey_t key, cval_t val, uint32_t val_size);

// remove the node from the list with key key
uint8_t remove_key(dbLL_t *list, ckey_t key);

// search list for key. If the key is found, return the value. 
// If the key is not found, NULL is returned
cval_t search(dbLL_t *list, ckey_t key);

// prints the entire list to stdout
void rep_list(dbLL_t *list);

