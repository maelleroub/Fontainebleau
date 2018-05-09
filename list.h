#ifndef LIST_H_
#define LIST_H_

#include<stdlib.h>
#include<stdio.h>

struct list
{
  struct list *next;
  void* data;
};

struct list* list_create(void *data);

struct list* list_init(void *data);

int list_is_empty(struct list *list);

size_t list_len(struct list *list);

void list_push_front(struct list *list, struct list *elm);

struct list* list_pop_front(struct list *list);

void list_push_back(struct list *list, struct list *elm);

void list_print_int(struct list *list);

void list_delete(struct list *list);

struct list* list_copy(struct list *list);

void* list_get(struct list *list, size_t n);

#endif
