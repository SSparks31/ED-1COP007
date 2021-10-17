#ifndef MODULE_QUEUE_H
#define MODULE_QUEUE_H

typedef struct queue* Queue;
typedef struct queue_pos* Queue_pos;
typedef void* Queue_elem;

Queue create_queue();

int queue_get_size(Queue queue);

Queue_elem queue_get_elem(Queue queue, Queue_pos pos);

Queue_pos queue_insert(Queue queue, Queue_elem elem);

void queue_remove(Queue queue);

Queue_pos queue_get_first(Queue queue);

Queue_pos queue_get_next(Queue queue, Queue_pos pos);

Queue_pos queue_get_last(Queue queue);

void queue_destroy(Queue* queue);

#endif