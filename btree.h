#ifndef BTREE_H_
#define BTREE_H_

#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"vector.h"

struct BTree
{
  int degree;
  struct vector *keys;
  struct vector *children;
};

struct BTree* bt_init(int degree, struct vector *keys);

struct BTree* bt_create(int degree, struct vector *keys);

int bt_is_empty(struct BTree *T);

void bt_breadth_first_print(struct BTree *T);

int bt_size(struct BTree *T);

int bt_height(struct BTree *T);

#endif
