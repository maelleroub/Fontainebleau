#ifndef BTREE_H_
#define BTREE_H_

#include<stdio.h>
#include<stdlib.h>
#include"queue.h"
#include"list.h"

struct BTree
{
  int degree;
  struct list *keys;
  struct list *children;
};

struct BTree* bt_init(int degree, struct list *keys);

struct BTree* bt_create(int degree, struct list *keys);

void bt_breadth_first_print(struct BTree *B);

#endif
