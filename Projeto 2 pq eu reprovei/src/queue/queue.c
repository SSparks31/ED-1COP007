#include "queue.h"

#include <stdio.h>
#include <stdlib.h>

struct queue {
    Queue_pos first;
    Queue_pos last;

    int size;
};

struct queue_pos {
    Queue_elem elem;

    Queue_pos next;
};

Queue create_queue() {
    Queue queue = malloc(sizeof(struct queue));
    if (!queue) {
        return NULL;
    }

    queue->first = NULL;
    queue->last = NULL;
    queue->size = 0;

    return queue;
}

int queue_get_size(Queue queue) {
    if (!queue) {
        return -1;
    }

    return queue->size;
}

Queue_elem queue_get_elem(Queue queue, Queue_pos pos) {
    if (!queue || !pos) {
        return NULL;
    }

    return pos->elem;
}

Queue_pos queue_insert(Queue queue, Queue_elem elem) {
    if (!queue || !elem) {
        return NULL;
    }

    Queue_pos new_pos = malloc(sizeof(struct queue_pos));
    if (!new_pos) {
        return NULL;
    }

    new_pos->elem = elem;
    new_pos->next = NULL;

    Queue_pos last = queue_get_last(queue);
    if (last) {
        last->next = new_pos;
    } else {
        queue->first = new_pos;
    }

    queue->last = new_pos;

    ++queue->size;

    return new_pos;
}

void queue_remove(Queue queue) {
    if (!queue || queue_get_size(queue) == 0) {
        return;
    }

    Queue_pos first = queue_get_first(queue);
    Queue_pos next = queue_get_next(queue, first);

    queue->first = next;
    
    if (!next) {
        queue->last = NULL;
    }

    free(first);

    --queue->size;
}

Queue_pos queue_get_first(Queue queue) {
    if (!queue) {
        return NULL;
    }

    return queue->first;
}

Queue_pos queue_get_next(Queue queue, Queue_pos pos) {
    if (!queue || !pos) {
        return NULL;
    }

    return pos->next;
}

Queue_pos queue_get_last(Queue queue) {
    if (!queue) {
        return NULL;
    }

    return queue->last;
}

void queue_destroy(Queue* queue) {
    if (!queue || !*queue) {
        return;
    }

    if (queue_get_size(*queue) != 0) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da fila nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    while (queue_get_size(*queue) != 0) {
        queue_remove(*queue);
    }

    free(*queue);
    *queue = NULL;
}