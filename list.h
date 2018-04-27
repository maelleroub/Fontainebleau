#ifndef LIST_H_
#define LIST_H_

struct list
{
  struct list *next;
  int data;
};

int list_is_empty(struct list *list);

size_t list_len(struct list *list);

void list_push_front(struct list *list, struct list *elm);

struct list* list_pop_front(struct list *list);

void list_push_back(struct list *list, struct list *elm);

void list_print(struct list *list);

#endif