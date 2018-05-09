#include"list.h"

struct list* list_create(void *data)
{
  struct list *l = malloc(sizeof(struct list));
  l->next = NULL;
  l->data = data;
  return l;
}

struct list* list_init(void *data)
{
  struct list *l = malloc(sizeof(struct list));
  l->data = NULL;
  l->next = list_create(data);
  return l;
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
    list->next = l->next;
  return l;
}

void list_push_back(struct list *list, struct list *elm)
{
  while(list->next)
    list = list->next;
  list->next = elm;
}

void list_print_int(struct list *list)
{
  if(!list_is_empty(list))
  {
    list = list->next;
    printf("%d", *((int*) list->data));
    while(list->next)
    {
      if(!list->next->data)
        printf(" -> None");
      else
        printf(" -> %d", *((int*) list->next->data));
      list = list->next;
    }
    printf("\n");
  }
}

void list_delete(struct list *list)
{
  struct list *l = list;
  while(list)
  {
    l = list->next;
    free(list);
    list = l;
  }
}

struct list* list_copy(struct list *list)
{
  struct list *l = list_create(NULL);
  while(list->next)
  {
    list = list->next;
    list_push_back(l, list_create(list->data));
  }
  return l;
}
