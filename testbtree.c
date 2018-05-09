#include"btree.h"

int main()
{
  int *n = malloc(sizeof(int));
  *n = 0;
  struct list *rootkeys = list_init(n);
  list_push_back(rootkeys, list_create(n));
  struct BTree *root = bt_init(2, rootkeys);
  struct BTree *x = list_get(root->children, 0);
  struct BTree *a = bt_create(2, rootkeys);
  struct BTree *b = bt_create(2, rootkeys);
  struct BTree *c = bt_create(2, rootkeys);
  list_push_back(x->children, list_create(a));
  list_push_back(x->children, list_create(b));
  list_push_back(x->children, list_create(c));
  bt_breadth_first_print(root);
  return 0;
}
