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
  T = T->left;
  while(T->right)
    T = T->right;
  return T;
}

struct binTree* bst_min(struct binTree *T)
{
  if(bt_is_empty(T))
    return NULL;
  T = T->left;
  while(T->left)
    T = T->left;
  return T;
}

struct binTree* bst_search(struct binTree *T, int x)
{
  if(bt_is_empty(T))
    return T;
  if(T->data == NULL)
    return bst_search(T->left, x);
  if(x == *T->data)
    return T;
  if(x < *T->data)
    return bst_search(T->left, x);
  return bst_search(T->right, x);
}

static struct binTree* _bst_insert_leaf(struct binTree* T, int x)
{
  if(!T)
    return bt_create(x);
  if(x <= *T->data)
    T->left = _bst_insert_leaf(T->left, x);
  else
    T->right = _bst_insert_leaf(T->right, x);
  return T;
}

void bst_insert_leaf(struct binTree *T, int x)
{
  T->left = _bst_insert_leaf(T->left, x);
}

static struct binTree* _bst_delete_max(struct binTree *T, int *x)
{
  if(bt_is_empty(T))
    return NULL;
  if(bt_is_empty(T->right))
  {
    struct binTree *N = T->left;
    *x = *(T->data);
    free(T->data);
    free(T);
    return N;
  }
  T->right = _bst_delete_max(T->right, x);
  return T;
}

static struct binTree* _bst_delete_min(struct binTree *T, int *x)
{
  if(bt_is_empty(T))
    return NULL;
  if(bt_is_empty(T->left))
  {
    struct binTree *N = T->right;
    *x = *(T->data);
    free(T->data);
    free(T);
    return N;
  }
  T->left = _bst_delete_min(T->left, x);
  return T;
}

static struct binTree* _bst_delete_elm(struct binTree *T, int x)
{
  if(!T)
    return T;
  if(x < *T->data)
  {
    T->left = _bst_delete_elm(T->left, x);
    return T;
  }
  if(x > *T->data)
  {
    T->right = _bst_delete_elm(T->right, x);
    return T;
  }
  //Node to delete
  if(bt_is_empty(T->left))
  {
    if(bt_is_empty(T->right))
    {
      free(T->data);
      free(T);
      return NULL;
    }
    int *d = malloc(sizeof(int));
    T->right = _bst_delete_min(T->right, d);
    *T->data = *d;
    free(d);
    return T;
  }
  int *d = malloc(sizeof(int));
  T->left = _bst_delete_max(T->left, d);
  *T->data = *d;
  free(d);
  return T;
}

void bst_delete_elm(struct binTree *T, int x)
{
  T->left = _bst_delete_elm(T->left, x);
}
