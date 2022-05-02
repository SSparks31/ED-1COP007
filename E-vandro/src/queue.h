#ifndef LIB_QUEUE_H
#define LIB_QUEUE_H

typedef struct queue* Queue;
typedef void* Queue_elem;

Queue queue_create(int max_length);

int queue_is_empty(Queue queue);

void queue_insert(Queue queue, Queue_elem elem);

Queue_elem queue_remove(Queue queue);

void queue_destroy(Queue* queue);

#endif