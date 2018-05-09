#include"btree.h"

struct BTree* bt_create(int degree, struct list *keys)
{
  struct BTree *B = malloc(sizeof(struct BTree));
  B->degree = degree;
  B->keys = keys;
  struct list *c = malloc(sizeof(struct list));
  c->next = NULL;
  B->children = c;
  return B;
}

struct BTree* bt_init(int degree, struct list *keys)
{
  struct BTree *B = malloc(sizeof(struct BTree));
  B->degree = degree;
  B->keys = NULL;
  B->children = list_init(bt_create(degree, keys));
  return B;
}

void bt_breadth_first_print(struct BTree *T)
{
  T = list_get(T->children, 0);
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
      size_t n = list_len(B->keys);
      printf("%d", *(int*)(list_get(B->keys, 0)));
      for(size_t i = 1; i < n; i++)
        printf("/%d", *(int*)(list_get(B->keys, i)));
      printf("  ");
      if(!list_is_empty(B->children))
      {
        for(size_t j = 0; j < n + 1; j++)
        {
          queue_push(q, list_get(B->children, j));
        }
      }
    }
  }
  free(change);
  queue_delete(q);
}
