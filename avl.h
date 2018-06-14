#ifndef AVL_H_
#define AVL_H_

#include<stdlib.h>
#include<stdio.h>
#include"queue.h"

struct AVL
{
  int *data;
  struct AVL *left;
  struct AVL *right;
  int balance;
};

struct AVL* avl_init(int n);

struct AVL* avl_create(int n);

int avl_is_empty(struct AVL *A);

int avl_size(struct AVL *A);

int avl_height(struct AVL *A);

int avl_width(struct AVL *A);

struct AVL* avl_max(struct AVL *A);

struct AVL* avl_min(struct AVL *A);

struct AVL* avl_search(struct AVL *A, int x);

void avl_breadth_first_print(struct AVL *A);

void avl_ugly_print(struct AVL *A);

void avl_insert(struct AVL *A, int x);

void avl_delete_elm(struct AVL *A, int x);

void avl_delete(struct AVL *A);

#endif
