#include"vector.h"

struct vector* vector_create(size_t c)
{
  struct vector *v = malloc(sizeof(struct vector));
  v->data = malloc(c * sizeof(void*));
  v->capacity = c;
  v->size = 0;
  return v;
}

int vector_is_empty(struct vector *v)
{
  return !v->size;
}

void vector_insert_at(struct vector *v, size_t a, void *x)
{
  if(v->size >= v->capacity || a > v->size)
    return;
  for(size_t j = v->size; j > a; j--)
    v->data[j] = v->data[j - 1];
  v->data[a] = x;
  v->size++;
}

void vector_delete_at(struct vector *v, size_t a)
{
  if(a >= v->size)
    return;
  for(size_t j = a; j < v->size - 1; j++)
    v->data[j] = v->data[j + 1];
  v->size--;
}

void vector_print_int(struct vector *v)
{
  if(vector_is_empty(v))
    return;
  for(size_t i = 0; i < v->size - 1; i++)
    printf("%d -> ", *(int*)v->data[i]);
  printf("%d\n", *(int*)v->data[v->size - 1]);
}

int main()
{
  struct vector *v = vector_create(5);
  int* a = malloc(sizeof(int));
  *a = 3;
  int* b = malloc(sizeof(int));
  *b = 1;
  int* c = malloc(sizeof(int));
  *c = 4;
  int* d = malloc(sizeof(int));
  *d = 2;
  int* e = malloc(sizeof(int));
  *e = 7;
  vector_insert_at(v, 0, a);
  vector_print_int(v);
  vector_insert_at(v, 1, b);
  vector_print_int(v);
  vector_insert_at(v, 0, c);
  vector_print_int(v);
  vector_insert_at(v, 0, d);
  vector_print_int(v);
  vector_insert_at(v, 2, e);
  vector_print_int(v);
  vector_delete_at(v, 4);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  vector_delete_at(v, 0);
  vector_print_int(v);
  return 1;
}
