//
// Created by leo on 3/26/21.
//

#include <stdio.h>

#include "../include/stack.h"
#include "../include/utils.h"

#define STACK_SIZE 1000
#define KGRN  "\x1B[32m"

int main()
{
    stack_t *stack = stack_create(sizeof(int));

    for (int i = 0; i <= STACK_SIZE; ++i)
        stack_push(stack, &i);

    int test;
    for (int i = STACK_SIZE; i > STACK_SIZE / 2; i--) {
        stack_pop(stack, &test);
        (ASSERT_RETURN(test == i, 1));
    }

    stack_free(stack);

    printf("%sAll tests passed for %s.", KGRN, __FILE__);
}
