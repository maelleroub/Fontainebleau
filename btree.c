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
          queue_push(q, vector_get(B->children, j));
        }
      }
    }
  }
  free(change);
  queue_delete(q);
}
