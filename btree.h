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

void bt_breadth_first_print(struct BTree *B);

#endif
