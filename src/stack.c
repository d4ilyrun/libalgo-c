//
// Created by leo on 3/26/21.
//

#include "../include/stack.h"

stack_t *stack_create(size_t size_of_type)
{
    return list_create(size_of_type);
}

node_t *stack_push(stack_t *stack, void *data)
{
    return list_append(stack, data);
}

void *stack_pop(stack_t *stack, void *out)
{
    return list_pop_last(stack, out);
}

void stack_free(stack_t *stack)
{
    list_free(stack);
}

int stack_empty(stack_t *stack)
{
    return stack->length == 0;
}
