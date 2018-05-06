#ifndef AVL_H_
#define AVL_H_

#include<stdlib.h>
#include<stdio.h>

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

void avl_ugly_print(struct AVL *A);

#endif
