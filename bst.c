#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include"bst.h"
#include"bintree.h"
#include"queue.h"
#include"list.h"

struct binTree* bst_max(struct binTree *T)
{
  if(bt_is_empty(T))
    return NULL;
  while(T->right)
    T = T->right;
  return T;
}

struct binTree* bst_min(struct binTree *T)
{
  if(bt_is_empty(T))
    return NULL;
  while(T->left)
    T = T->left;
  return T;
}

struct binTree* bst_search(struct binTree *T, int x)
{
  if(bt_is_empty(T))
    return T;
  if(x == T->data)
    return T;
  if(x < T->data)
    return bst_search(T->left, x);
  return bst_search(T->right, x);
}

struct binTree* bst_insert_leaf(struct binTree *T, int x)
{
  if(bt_is_empty(T))
    return bt_create(x);
  if(x <= T->data)
    T->left = bst_insert_leaf(T->left, x);
  else
    T->right = bst_insert_leaf(T->right, x);
  return T;
}
