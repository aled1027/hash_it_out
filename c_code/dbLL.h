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
void insert(dbLL_t *list, ckey_t key, cval_t val, uint32_t val_size);
uint8_t remove_key(dbLL_t *list, ckey_t key);
cval_t search(dbLL_t *list, ckey_t key);
void rep_list(dbLL_t *list);

