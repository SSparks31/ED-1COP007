#ifndef MODULE_STACK_H
#define MODULE_STACK_H

typedef struct stack* Stack;
typedef struct stack_pos* Stack_pos;
typedef void* Stack_elem;

Stack create_stack();

int stack_get_size(Stack stack);

Stack_elem stack_get_elem(Stack stack, Stack_pos pos);

Stack_pos stack_insert(Stack stack, Stack_elem elem);

void stack_remove(Stack stack);

Stack_pos stack_get_top(Stack stack);

Stack_pos stack_get_prev(Stack stack, Stack_pos pos);

void stack_destroy(Stack* stack);

#endif