#include<stdlib.h>
#include<stdio.h>
#include<assert.h>
#include"queue.h"

void queue_init(struct queue *queue)
{
  queue->size = 0;
  queue->list = NULL;
}

int queue_is_empty(struct queue *queue)
{
  return queue->size == 0;
}

void queue_push(struct queue *queue, void *elm)
{
  struct q_list *l = malloc(sizeof(struct q_list*));
  l->data = elm;
  if(queue->list)
  {
    l->next = queue->list->next;
    queue->list->next = l;
  }
  else
    l->next = l;
  queue->list = l;
  queue->size++;
}

void* queue_pop(struct queue *queue)
{
  if(queue->size == 0)
    return NULL;
  if(queue->size == 1)
  {
    void* data = queue->list->data;
    free(queue->list);
    queue->list = NULL;
    queue->size = 0;
    return data;
  }
  struct q_list *l = queue->list->next;
  queue->list->next = queue->list->next->next;
  void *data = l->data;
  free(l);
  queue->size--;
  return data;
}

/*int main()
{
  int *a = malloc(sizeof(int*));
  *a = 1;
  int *b = malloc(sizeof(int*));                             
  *b = 3;
  int *c =malloc(sizeof(int*));                             
  *c = 4;
  int *d = malloc(sizeof(int*));                             
  *d = 7;
  int *e = malloc(sizeof(int*));                             
  *e = 2;
  int *f = malloc(sizeof(int*));                             
  *f = 5;
  struct queue *q = malloc(sizeof(struct queue*));
  queue_init(q);
  queue_push(q, a);
  queue_push(q,b);
  queue_push(q,c);
  assert(queue_pop(q) == a);
  assert(queue_pop(q) == b);
  queue_push(q,d);
  assert(queue_pop(q) == c);
  assert(queue_pop(q) == d);
  assert(queue_pop(q) == NULL);
  queue_push(q,e);
  assert(queue_pop(q) == e);
  return 1;
}*/
