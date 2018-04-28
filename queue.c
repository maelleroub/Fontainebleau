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
  struct q_list *l = malloc(sizeof(struct q_list));
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

void queue_delete(struct queue *queue)
{
  struct q_list *l1 = queue->list;
  struct q_list *l2 = l1;
  while(queue->size)
  {
    l2 = l1->next;
    free(l1);
    l1 = l2;
    queue->size--;
  }
  free(queue);
}
