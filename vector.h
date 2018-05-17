#ifndef VECTOR_H_
#define VECTOR_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct vector
{
  void **data;
  size_t capacity;
  size_t size;
};

struct vector* vector_create(size_t c);

int vector_is_empty(struct vector *v);

int vector_insert_at(struct vector *v, size_t a, void *x);

int vector_insert_int_at(struct vector *v, size_t a, int x);

int vector_delete_at(struct vector *v, size_t a);

void vector_print_int(struct vector *v);

void vector_delete(struct vector *v);

#endif
