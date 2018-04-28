#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<assert.h>
#include"queue.h"
#include"list.h"

struct binTree
{
  int data;
  struct binTree *left;
  struct binTree *right;
};

int bt_is_empty(struct binTree *T)
{
  return T == NULL;
}

size_t bt_size(struct binTree *T)
{
  return (bt_is_empty(T)) ? 0 : 1 + bt_size(T->left) + bt_size(T->right);
}

static int _max(int a, int b)
{
  return (a >= b) ? a : b;
}

size_t bt_height(struct binTree *T)
{
  return (bt_is_empty(T)) ? -1 : 1 + _max(bt_height(T->left), bt_height(T->right));
}

size_t bt_width(struct binTree *T)
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

struct list* bt_to_hierarchy(struct binTree *T)
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
        struct binTree *B = v;
        struct list *l1 = malloc(sizeof(struct list));
        if(bt_is_empty(B))
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

struct binTree* hierarchy_to_bt(struct list *list)
{
  if(list_is_empty(list))
    return NULL;
  struct binTree *root = malloc(sizeof(struct binTree));
  root->data = *((int*) list_pop_front(list)->data);
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, root);
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
        struct binTree *btleft = malloc(sizeof(struct binTree));
        btleft->data = *((int*) l->data);
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
        struct binTree *btright = malloc(sizeof(struct binTree));
        btright->data = *((int*) r->data);
        cur->right = btright;
        queue_push(q, btright);
      }
    }
    if(!cur)
    {
      queue_push(q, NULL);
      queue_push(q, NULL);
    }
  }
  return root;
}

int bt_equals(struct binTree *A, struct binTree *B)
{
  if(bt_is_empty(A) ^ bt_is_empty(B))
    return 0;
  if(bt_is_empty(A) && bt_is_empty(B))
    return 1;
  if(A->data != B->data)
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
    printf("%d\n", T->data);
    _bt_ugly_print(T->right, depth + 1);
  }
  else
    printf("\n");
}

void bt_ugly_print(struct binTree *T)
{
  _bt_ugly_print(T, 0);
}

void bt_breadth_first_print(struct binTree *T)
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
        struct binTree *B = v;
        if(bt_is_empty(B))
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