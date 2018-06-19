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

static struct BTree* _bt_half(struct BTree *T, int first)
  //Generates a btree from half of the btree given as argument
{
  if(first)
  {
    struct vector *keys = vector_create(T->degree * 2 - 1);
    struct BTree *R = bt_create(T->degree, keys);
    for(int i = 0; i < T->degree - 1; i++)
    {
      vector_insert_at(R->keys, i, T->keys->data[i]);
      if(T->children->size)
        vector_insert_at(R->children, i, T->children->data[i]);
    }
    if(T->children->size)
      vector_insert_at(R->children, T->degree - 1, T->children->data[T->degree - 1]);
    return R;
  }
  struct vector *keys = vector_create(T->degree * 2 - 1);
  struct BTree *R = bt_create(T->degree, keys);
  for(int i = T->degree; i < T->degree * 2 - 1; i++)
  {
    vector_insert_at(R->keys, i - T->degree, T->keys->data[i]);
    if(T->children->size)
      vector_insert_at(R->children, i - T->degree, T->children->data[i]);
  }
  if(T->children->size)
    vector_insert_at(R->children, T->degree - 1, T->children->data[T->degree * 2 - 1]);
  return R;
}

static struct BTree* _bt_insert_downwards(struct BTree *T, int x)
{
  if((int)T->keys->size == T->degree * 2 - 1) //Full node
  {
    struct BTree *L = _bt_half(T, 1);
    struct BTree *R = _bt_half(T, 0);
    struct vector *keys = vector_create(T->degree * 2 - 1);
    vector_insert_at(keys, 0, T->keys->data[T->degree - 1]);
    struct BTree *parent = bt_create(T->degree, keys);
    vector_insert_at(parent->children, 0, L);
    vector_insert_at(parent->children, 1, R);
    if(x <= *(int *)parent->keys->data[0])
      parent->children->data[0] = _bt_insert_downwards(parent->children->data[0], x);
    else
      parent->children->data[1] = _bt_insert_downwards(parent->children->data[1], x);
    return parent;
  }
  if(T->children->size)
  {
    printf("%zu\n", T->children->size);
    for(size_t i = 0; i < T->keys->size; i++)
    {
      if(x <= *(int *)T->keys->data[i])
      {
        T->children->data[i] = _bt_insert_downwards(T->children->data[i], x);
        return T;
      }
    }
    T->children->data[T->keys->size] = _bt_insert_downwards(T->children->data[T->keys->size], x);
    return T;
  }
  for(size_t i = 0; i < T->keys->size; i++)
  {
    if(x <= *(int *)T->keys->data[i])
    {
      int *a = malloc(sizeof(int));
      *a = x;
      vector_insert_at(T->keys, i, a);
      return T;
    }
  }
  int *a = malloc(sizeof(int));
  *a = x;
  vector_insert_at(T->keys, T->keys->size, a);
  return T;
}

void bt_insert_downwards(struct BTree *T, int x)
{
  T->children->data[0] = _bt_insert_downwards(T->children->data[0], x);
}
