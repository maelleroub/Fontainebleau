#include"btree.h"

struct BTree* bt_create(int degree, struct vector *keys)
{
  struct BTree *B = malloc(sizeof(struct BTree));
  B->degree = degree;
  B->keys = keys;
  B->children = vector_create(degree * 2);
  return B;
}

struct BTree* bt_init(int degree, struct vector *keys)
{
  struct BTree *B = malloc(sizeof(struct BTree));
  B->degree = degree;
  B->keys = NULL;
  struct vector *c = vector_create(degree * 2);
  vector_insert_at(c, 0, bt_create(degree, keys));
  B->children = c;
  return B;
}

int bt_is_empty(struct BTree *T)
{
  return !T || (!T->keys && !vector_get(T->children, 0));
}

static struct BTree* child(struct BTree *T, size_t i)
{
  return vector_get(T->children, i);
}

void bt_breadth_first_print(struct BTree *T)
{
  T = vector_get(T->children, 0);
  void *change = malloc(sizeof(void));
  struct queue *q = malloc(sizeof(struct queue));
  queue_init(q);
  queue_push(q, T);
  queue_push(q, change);
  while(!queue_is_empty(q))
  {
    void* v = queue_pop(q);
    if(v == change)
    {
      printf("\n");
      if(!queue_is_empty(q))
        queue_push(q, change);
    }
    else
    {
      struct BTree *B = v;
      printf("%d", *(int*)(vector_get(B->keys, 0)));
      for(size_t i = 1; i < B->keys->size; i++)
        printf("/%d", *(int*)(vector_get(B->keys, i)));
      printf("  ");
      if(!vector_is_empty(B->children))
      {
        for(size_t j = 0; j < B->children->size; j++)
        {
          queue_push(q, child(B, j));
        }
      }
    }
  }
  free(change);
  queue_delete(q);
}

int bt_size(struct BTree *T)
{
  if(!T->keys)
    return vector_is_empty(T->children) ? 0 : bt_size(child(T,0));
  size_t s = 1;
  for(size_t i = 0; i < T->children->size; i++)
    s += bt_size(child(T, i));
  return s;
}

int bt_height(struct BTree *T) //B-Tree: all children on same level
{
  if(!T)
    return -1;
  if(!T->keys)
    return bt_height(child(T, 0));
  return 1 + bt_height(child(T, 0));
}

int bt_width(struct BTree *T) //Width of last level: Level n+1 larger than level n
{
  if(!T->keys)
    return vector_is_empty(T->children) ? 0 : bt_width(child(T, 0));
  if(T->children->size)
  {
    int s = 0;
    for(size_t i = 0; i < T->children->size; i++)
      s += bt_width(child(T, i));
    return s;
  }
  return 1;
}
