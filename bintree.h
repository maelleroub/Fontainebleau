#ifndef BIN_TREE_H_
#define BIN_TREE_H_

#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include"queue.h"
#include"list.h"
#include"avl.h"
#include"avl.h"

struct binTree
{
  int *data;
  struct binTree *left;
  struct binTree *right;
};

struct binTree* bint_init(int n);

struct binTree* bint_create(int n);

int bint_is_empty(struct binTree *T);

size_t bint_size(struct binTree *T);

size_t bint_height(struct binTree *T);

int bint_is_degenerate(struct binTree *T);

int bint_is_perfect(struct binTree *T);

size_t bint_width(struct binTree *T);

int bint_is_bst(struct binTree *T);

int bint_is_balanced(struct binTree *T);

int bint_is_avl(struct binTree *T);

struct list* bint_to_hierarchy(struct binTree *T);

struct binTree* hierarchy_to_bint(struct list *list);

int bint_equals(struct binTree *A, struct binTree *B);

void bint_ugly_print(struct binTree *T);

void bint_breadth_first_print(struct binTree *T);

void bint_delete(struct binTree *T);

struct AVL* bint_to_avl(struct binTree *T);

#endif
