#include<stdlib.h>
#include<stdio.h>
#include"list.h"

struct BST
{
  int data;
  struct BST *left;
  struct BST *right;
};

struct BST* bst_create(int n);

int bst_is_empty(struct BST *T);

size_t bst_size(struct BST *T);

struct BST* bst_max(struct BST *T);

struct BST* bst_min(struct BST *T);

struct BST* bst_search(struct BST *T, int x);

size_t bst_height(struct BST *T);

int bst_is_degenerate(struct BST *T);

int bst_is_perfect(struct BST *T);

size_t bst_width(struct BST *T);

struct list* bst_to_hierarchy(struct BST *T);

struct BST* hierarchy_to_bst(struct list *l);

int bst_equals(struct BST *A, struct BST *B);

void bst_ugly_print(struct BST *T);

void bst_breadth_first_print(struct BST *T);

void bst_delete(struct BST *T);
