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

int main()
{
  struct vector *v = vector_create(5);
  vector_insert_int_at(v, 0, 3);
  vector_print_int(v);
  vector_insert_int_at(v, 1, 4);
  vector_print_int(v);
  vector_insert_int_at(v, 0, 2);
  vector_print_int(v);
  vector_insert_int_at(v, 0, 7);
  vector_print_int(v);
  vector_insert_int_at(v, 2, 8);
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
