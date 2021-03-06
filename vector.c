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

void* vector_get(struct vector *v, size_t a)
{
  if(a >= v->size)
    return NULL;
  return v->data[a];
}

int vector_insert_at(struct vector *v, size_t a, void *x)
{
  if(v->size >= v->capacity || a > v->size)
    return 0;
  for(size_t j = v->size; j > a; j--)
    v->data[j] = v->data[j - 1];
  v->data[a] = x;
  v->size++;
  return 1;
}

int vector_insert_int_at(struct vector *v, size_t a, int x)
{
  int *y = malloc(sizeof(int));
  *y = x;
  return vector_insert_at(v, a, y);
}

int vector_delete_at(struct vector *v, size_t a)
{
  if(a >= v->size)
    return 0;
  free(v->data[a]);
  for(size_t j = a; j < v->size - 1; j++)
    v->data[j] = v->data[j + 1];
  v->size--;
  return 1;
}

void vector_print_int(struct vector *v)
{
  if(vector_is_empty(v))
    return;
  for(size_t i = 0; i < v->size - 1; i++)
    printf("%d -> ", *(int*)v->data[i]);
  printf("%d\n", *(int*)v->data[v->size - 1]);
}

void vector_delete(struct vector *v)
{
  for(size_t i = 0; i < v->size; i++)
    free(v->data[i]);
  free(v->data);
  free(v);
}
