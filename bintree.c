#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include"queue.h"
#include"list.h"
#include"bintree.h"

struct binTree* bt_init(int n)
{
  struct binTree *T = malloc(sizeof(struct binTree));
  T->data = NULL;
  T->right = NULL;
  T->left = bt_create(n);
  return T;
}

struct binTree* bt_create(int n)
{
  struct binTree *T = malloc(sizeof(struct binTree));
  int *data = malloc(sizeof(int));
  *data = n;
  T->data = data;
  T->left = NULL;
  T->right = NULL;
  return T;
}

int bt_is_empty(struct binTree *T)
{
  return !T || (T->data == NULL && !T->left);
}

size_t bt_size(struct binTree *T)
{
  if(!T)
    return 0;
  if(T->data == NULL)
  {
    if(!T->left)
      return 0;
    T = T->left;
  }
  return 1 + bt_size(T->left) + bt_size(T->right);
}

static int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

size_t bt_height(struct binTree *T)
{
  if(bt_is_empty(T))
    return -1;
  if(T->data == NULL)
    T = T->left;
  return 1 + _max(bt_height(T->left), bt_height(T->right));
}

int bt_is_degenerate(struct binTree *T)
{
  if(bt_is_empty(T))
    return 1;
  if(T->left && T->right)
    return 0;
  return bt_is_degenerate(T->left) && bt_is_degenerate(T->right);
}

static size_t _left_path_len(struct binTree *T)
{
  size_t x;
  for(x = 0; T; x++)
    T = T->left;
  return x;
}

static int _bt_is_perfect(struct binTree *T, size_t h, size_t lvl)
{
  if(bt_is_empty(T->left) ^ bt_is_empty(T->right))
    return 0;
  if(T->left)
    return _bt_is_perfect(T->left, h, lvl + 1) && _bt_is_perfect(T->right, h, lvl + 1);
  return h == lvl;
}

int bt_is_perfect(struct binTree *T)
{
  if(bt_is_empty(T))
    return 1;
  T = T->left;
  size_t h = _left_path_len(T);
  return _bt_is_perfect(T, h, 1);
}

size_t bt_width(struct binTree *T)
{
  if(bt_is_empty(T))
    return 0;
  T = T->left;
  int maxw = 0;
  int w = 0;
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, T);
  queue_push(q, NULL);
  while(!queue_is_empty(q))
  {
    struct binTree *B = queue_pop(q);
    if(!B)
    {
      maxw = _max(w, maxw);
      w = 0;
      if(!queue_is_empty(q))
        queue_push(q, NULL);
    }
    else
    {
      w++;
      if(B->left)
        queue_push(q, B->left);
      if(B->right)
        queue_push(q, B->right);
    }
  }
  queue_delete(q);
  return (size_t) maxw;
}

static int _bt_is_bst(struct binTree *T, int *low, int *high)
{
  if(!T)
    return 1;
  if(low == NULL)
  {
    if(high != NULL && *T->data > *high)
      return 0;
    return _bt_is_bst(T->left, low, T->data) && _bt_is_bst(T->right, T->data, high);
  }
  if(high == NULL)
  {
    if(*T->data <= *low)
      return 0;
    return _bt_is_bst(T->left, low, T->data) && _bt_is_bst(T->right, T->data, high);
  }
  if(*T->data <= *low || *T->data > *high)
    return 0;
  return _bt_is_bst(T->left, low, T->data) && _bt_is_bst(T->right, T->data, high);
}

int bt_is_bst(struct binTree *T)
{
  if(bt_is_empty(T))
    return 1;
  T = T->left;
  return _bt_is_bst(T, NULL, NULL);
}

struct list* bt_to_hierarchy(struct binTree *T)
{
  struct list *l = malloc(sizeof(struct list));
  list_init(l);
  if (!bt_is_empty(T))
  {
    T = T->left;
    int nextlevel = 0;
    void *change = malloc(sizeof(void));
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    queue_push(q, T);
    queue_push(q, change);
    while(1)
    {
      void* v = queue_pop(q);
      if(v == change)
      {
        if(!nextlevel)
          break;
        nextlevel = 0;
        queue_push(q, change);
      }
      else
      {
        struct binTree *B = v;
        struct list *l1 = malloc(sizeof(struct list));
        list_init(l1);
        if(bt_is_empty(B))
        {
          l1->data = NULL;
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          l1->data = B->data;
          queue_push(q, B->left);
          queue_push(q, B->right);
          nextlevel = nextlevel || B->left || B->right;
        }
        list_push_back(l, l1);
      }
    }
    free(change);
    queue_delete(q);
  }
  return l;
}

struct binTree* hierarchy_to_bt(struct list *l)
{
  struct list *list = list_copy(l);
  if(list_is_empty(list))
    return NULL;
  struct list *x = list_pop_front(list);
  struct binTree *root = bt_init(*((int *) x->data));
  free(x);
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, root->left);
  while(!list_is_empty(list))
  {
    struct binTree *cur = queue_pop(q);
    struct list *l = list_pop_front(list);
    if(l && cur)
    {
      if(!l->data)
      {
        cur->left = NULL;
        queue_push(q, NULL);
      }
      else
      {
        struct binTree *btleft = bt_create(*((int *) l->data));
        cur->left = btleft;
        queue_push(q, btleft);
      }
    }
    struct list *r = list_pop_front(list);
    if(r && cur)
    {
      if(!r->data)
      {
        cur->right = NULL;
        queue_push(q, NULL);
      }
      else
      {
        struct binTree *btright = bt_create(*((int *) r->data));
        cur->right = btright;
        queue_push(q, btright);
      }
    }
    free(l);
    free(r);
    if(!cur)
    {
      queue_push(q, NULL);
      queue_push(q, NULL);
    }
  }
  queue_delete(q);
  list_delete(list);
  return root;
}

int bt_equals(struct binTree *A, struct binTree *B)
{
  if(bt_is_empty(A) ^ bt_is_empty(B))
    return 0;
  if(bt_is_empty(A) && bt_is_empty(B))
    return 1;
  if(A->data == NULL)
    return bt_equals(A->left, B->left);
  if(*A->data != *B->data)
    return 0;
  return bt_equals(A->left, B->left) && bt_equals(A->right, B->right);
}

static void _bt_ugly_print(struct binTree *T, int depth)
{
  if(!bt_is_empty(T))
  {
    _bt_ugly_print(T->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", *T->data);
    _bt_ugly_print(T->right, depth + 1);
  }
  else
    printf("\n");
}

void bt_ugly_print(struct binTree *T)
{
  if(bt_is_empty(T))
    return;
  _bt_ugly_print(T->left, 0);
}

void bt_breadth_first_print(struct binTree *T)
{
  if(!bt_is_empty(T))
  {
    T = T->left;
    int nextlevel = 0;
    void *change = malloc(sizeof(void));
    struct queue *q = malloc(sizeof(struct queue));
    queue_init(q);
    queue_push(q, T);
    queue_push(q, change);
    while(1)
    {
      void* v = queue_pop(q);
      if(v == change)
      {
        printf("\n");
        if(!nextlevel)
          break;
        nextlevel = 0;
        queue_push(q, change);
      }
      else
      {
        struct binTree *B = v;
        if(bt_is_empty(B))
        {
          printf("X  ");
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          printf("%d  ", *B->data);
          queue_push(q, B->left);
          queue_push(q, B->right);
          nextlevel = nextlevel || B->left || B->right;
        }
      }
    }
    free(change);
    queue_delete(q);
  }
}

void bt_delete(struct binTree *T)
{
  if(T)
  {
    bt_delete(T->left);
    bt_delete(T->right);
    free(T->data);
    free(T);
  }
}
