#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include<stdlib.h>

struct binTree
{
  int *data;
  struct binTree *left;
  struct binTree *right;
};

struct binTree* bt_init(int n);

struct binTree* bt_create(int n);

int bt_is_empty(struct binTree *T);

size_t bt_size(struct binTree *T);

size_t bt_height(struct binTree *T);

int bt_is_degenerate(struct binTree *T);

int bt_is_perfect(struct binTree *T);

size_t bt_width(struct binTree *T);

int bt_is_bst(struct binTree *T);

int bt_is_balanced(struct binTree *T);

int bt_is_avl(struct binTree *T);

struct list* bt_to_hierarchy(struct binTree *T);

struct binTree* hierarchy_to_bt(struct list *list);

int bt_equals(struct binTree *A, struct binTree *B);

void bt_ugly_print(struct binTree *T);

void bt_breadth_first_print(struct binTree *T);

void bt_delete(struct binTree *T);

#endif
