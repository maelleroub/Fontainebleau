#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include"bst.h"
#include"queue.h"
#include"list.h"

struct BST* bst_create(int n)
{
  struct BST *T = malloc(sizeof(struct BST));
  T->data = n;
  T->left = NULL;
  T->right = NULL;
  return T;
}

int bst_is_empty(struct BST *T)
{
  return T == NULL;
}

size_t bst_size(struct BST *T)
{
  return (bst_is_empty(T)) ? 0 : 1 + bst_size(T->left) + bst_size(T->right);
}

static int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

struct BST* bst_max(struct BST *T)
{
  if(bst_is_empty(T))
    return NULL;
  while(T->right)
    T = T->right;
  return T;
}

struct BST* bst_min(struct BST *T)
{
  if(bst_is_empty(T))
    return NULL;
  while(T->left)
    T = T->left;
  return T;
}

struct BST* bst_search(struct BST *T, int x)
{
  if(bst_is_empty(T))
    return T;
  if(x == T->data)
    return T;
  if(x < T->data)
    return bst_search(T->left, x);
  return bst_search(T->right, x);
}

size_t bst_height(struct BST *T)
{
  return (bst_is_empty(T)) ? -1 : 1 + _max(bst_height(T->left), bst_height(T->right));
}

int bst_is_degenerate(struct BST *T)
{
  if(bst_is_empty(T))
    return 1;
  if(T->left && T->right)
    return 0;
  return bst_is_degenerate(T->left) && bst_is_degenerate(T->right);
}

static size_t _left_path_len(struct BST *T)
{
  size_t x;
  for(x = 0; T; x++)
    T = T->left;
  return x;
}

static int _bst_is_perfect(struct BST *T, size_t h, size_t lvl)
{
  if(bst_is_empty(T->left) ^ bst_is_empty(T->right))
    return 0;
  if(T->left)
    return _bst_is_perfect(T->left, h, lvl + 1) && _bst_is_perfect(T->right, h, lvl + 1);
  return h == lvl;
}

int bst_is_perfect(struct BST *T)
{
  if(bst_is_empty(T))
    return 1;
  size_t h = _left_path_len(T);
  return _bst_is_perfect(T, h, 1);
}

size_t bst_width(struct BST *T)
{
  if(!T)
    return 0;
  int maxw = 0;
  int w = 0;
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, T);
  queue_push(q, NULL);
  while(!queue_is_empty(q))
  {
    struct BST *B = queue_pop(q);
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

struct list* bst_to_hierarchy(struct BST *T)
{
  struct list *l = malloc(sizeof(struct list));
  list_init(l);
  if (T)
  {
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
        struct BST *B = v;
        struct list *l1 = malloc(sizeof(struct list));
        list_init(l1);
        if(bst_is_empty(B))
        {
          l1->data = NULL;
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          l1->data = &(B->data);
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

struct BST* hierarchy_to_bst(struct list *l)
{
  struct list *list = list_copy(l);
  if(list_is_empty(list))
    return NULL;
  struct list *x = list_pop_front(list);
  struct BST *root = bst_create(*((int *) x->data));
  free(x);
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, root);
  while(!list_is_empty(list))
  {
    struct BST *cur = queue_pop(q);
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
        struct BST *bstleft = bst_create(*((int *) l->data));
        cur->left = bstleft;
        queue_push(q, bstleft);
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
        struct BST *bstright = bst_create(*((int *) r->data));
        cur->right = bstright;
        queue_push(q, bstright);
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

int bst_equals(struct BST *A, struct BST *B)
{
  if(bst_is_empty(A) ^ bst_is_empty(B))
    return 0;
  if(bst_is_empty(A) && bst_is_empty(B))
    return 1;
  if(A->data != B->data)
    return 0;
  return bst_equals(A->left, B->left) && bst_equals(A->right, B->right);
}

static void _bst_ugly_print(struct BST *T, int depth)
{
  if(!bst_is_empty(T))
  {
    _bst_ugly_print(T->left, depth + 1);
    for(int i = 0; i < depth; i++)
      printf("  ");
    printf("%d\n", T->data);
    _bst_ugly_print(T->right, depth + 1);
  }
  else
    printf("\n");
}

void bst_ugly_print(struct BST *T)
{
  _bst_ugly_print(T, 0);
}

void bst_breadth_first_print(struct BST *T)
{
  if (T)
  {
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
        struct BST *B = v;
        if(bst_is_empty(B))
        {
          printf("X  ");
          queue_push(q, NULL);
          queue_push(q, NULL);
        }
        else
        {
          printf("%d  ", B->data);
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

void bst_delete(struct BST *T)
{
  if(!bst_is_empty(T))
  {
    bst_delete(T->left);
    bst_delete(T->right);
    free(T);
  }
}
