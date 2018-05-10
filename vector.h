#ifndef VECTOR_H_
#define VECTOR_H_
#include<stdlib.h>
#include<stdio.h>
#include<string.h>

struct vector
{
  int *data;
  size_t capacity;
  size_t size;
};

struct vector* vector_create(size_t c);

#endif
