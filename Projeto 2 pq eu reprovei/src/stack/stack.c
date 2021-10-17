#include "stack.h"

#include <stdlib.h>
#include <stdio.h>

struct stack {
    Stack_pos top;

    int size;
};

struct stack_pos {
    Stack_elem elem;

    Stack_pos prev;
};

Stack create_stack() {
    Stack stack = malloc(sizeof(struct stack));
    if (!stack) {
        return NULL;
    }

    stack->top = NULL;
    stack->size = 0;

    return stack;
}

int stack_get_size(Stack stack) {
    if (!stack) {
        return -1;
    }

    return stack->size;
}

Stack_elem stack_get_elem(Stack stack, Stack_pos pos) {
    if (!stack || !pos) {
        return NULL;
    }

    return pos->elem;
}

Stack_pos stack_insert(Stack stack, Stack_elem elem) {
    if (!stack || !elem) {
        return NULL;
    }

    Stack_pos new_pos = malloc(sizeof(struct stack_pos));
    if (!new_pos) {
        return NULL;
    }

    new_pos->elem = elem;
    new_pos->prev = stack_get_top(stack);
    stack->top = new_pos;

    ++stack->size;

    return new_pos;
}

void stack_remove(Stack stack) {
    if (!stack || stack_get_size(stack) == 0) {
        return;
    }

    Stack_pos top = stack_get_top(stack);
    Stack_pos top_prev = stack_get_prev(stack, top);

    stack->top = top_prev;

    free(top);

    --stack->size;
}

Stack_pos stack_get_top(Stack stack) {
    if (!stack) {
        return NULL;
    }

    return stack->top;
}

Stack_pos stack_get_prev(Stack stack, Stack_pos pos) {
    if (!stack || !pos) {
        return NULL;
    }

    return pos->prev;
}

void stack_destroy(Stack* stack) {
    if (!stack || !*stack) {
        return;
    }

    if (stack_get_size(*stack) != 0) {
        printf("\n------------\n");
        printf("ATENCAO:\nO desalocamento de elementos da pilha nao e realizado automaticamente; caso seja necessario, modifique seu programa para realizar a remocao e desalocamento.\n");
    }

    while (stack_get_size(*stack) != 0) {
        stack_remove(*stack);
    }

    free(*stack);
    *stack = NULL;
}