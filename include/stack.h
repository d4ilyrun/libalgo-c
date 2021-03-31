//
// Created by leo on 3/26/21.
//

#ifndef LIBALGO_STACK_H
#define LIBALGO_STACK_H

#include "../include/list.h"

typedef list_t stack_t;

stack_t *stack_create(size_t size_of_type);
node_t  *stack_push(stack_t *stack, void *data);
void    *stack_pop(stack_t *stack, void *out);
void     stack_free(stack_t *stack);
int      stack_empty(stack_t *stack);

#endif //LIBALGO_STACK_H
