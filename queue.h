#ifndef QUEUE_H_
#define QUEUE_H_

struct q_list 
{
  struct q_list *next;
  void *data;
};

struct queue 
{
  struct q_list *list;
  size_t size;
};

void queue_init(struct queue *queue);

int queue_is_empty(struct queue *queue);

void queue_push(struct queue *queue, void *elm);

void* queue_pop(struct queue *queue);

void queue_delete(struct queue *queue);

#endif
