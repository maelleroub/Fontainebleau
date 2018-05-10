#include"vector.h"

struct vector* vector_create(size_t c)
{
  struct vector *v = malloc(sizeof(struct vector));
  v->data = malloc(c * sizeof(int));
  v->capacity = c;
  v->size = 0;
  return v;
}

void vector_insert(struct vector *v, int a)
{
  if(v->size >= v->capacity)
    return;
  size_t i = 0;
  while(i < v->size && a > v->data[i])
    i++;
  if(i < v->capacity)
  {
    for(size_t j = v->size; j > i; j--)
      v->data[j] = v->data[j - 1];
    v->data[i] = a;
    v->size++;
  }
}

void vector_delete(struct vector *v, int a)
{
  if(!v->size)
    return;
  size_t i = 0;
  while(i < v->size && a > v->data[i])
    i++;
  if(i < v->size && v->data[i] == a)
  {
    for(size_t j = i; j < v->size - 1; j++)
      v->data[j] = v->data[j + 1];
    v->size--;
  }
}

void vector_print_int(struct vector *v)
{
  for(size_t i = 0; i < v->size - 1; i++)
  {
    printf("%d -> ", v->data[i]);
  }
  printf("%d\n", v->data[v->size - 1]);
}

int main()
{
  struct vector *v = vector_create(5);
  vector_insert(v, 3);
  vector_print_int(v);
  vector_insert(v, 1);
  vector_print_int(v);
  vector_insert(v, 4);
  vector_print_int(v);
  vector_insert(v, 2);
  vector_print_int(v);
  vector_insert(v, 7);
  vector_print_int(v);
  vector_delete(v, 4);
  vector_print_int(v);
  vector_delete(v, 42);
  vector_print_int(v);
  vector_insert(v, 0);
  vector_print_int(v);
  vector_delete(v, 0);
  vector_print_int(v);
  vector_insert(v, 3);
  vector_print_int(v);
  return 1;
}
