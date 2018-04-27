#include<stdlib.h>
#include<stdio.h>
#include"list.h"

void list_init(struct list *list)
{
  list->next = NULL;
}

int list_is_empty(struct list *list)
{
  return list->next == NULL;
}

size_t list_len(struct list *list)
{
  size_t count = 0;
  while(list->next)
  {
    list = list->next;
    count++;
  }
  return count;
}

void list_push_front(struct list *list, struct list *elm)
{
  elm->next = list->next;
  list->next = elm;
}

struct list* list_pop_front(struct list *list)
{
  struct list *l = list->next;
  if(l)
  {
    list->next = l->next;
  }
  return l;
}

void list_push_back(struct list *list, struct list *elm)
{
  while(list->next)
    list = list->next;
  list->next = elm;
}

void list_print(struct list *list)
{
  if(!list_is_empty(list))
  {
    list = list->next;
    printf("%d", list->data);
    while(list->next)
    {
      printf(" -> %d", list->next->data);
      list = list->next;
    }
    printf("\n");
  }
}
