#include "../include/list.h"
#include "../include/stack.h"
#include "../include/utils.h"

#define KGRN  "\x1B[32m"
#define LIST_LENGTH 50000

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void f(void *data)
{
    int i = *(int *)data;
    i += 1;
    memcpy(data, &i, sizeof (int));
}

int compare(void *a, void *b)
{
    return *(int *)a >= *(int *)b;
}

void print(void *data)
{
    printf("%d\n", *(int *)data);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(sizeof(int));
    list->compare = compare;
    int test;

    for (int i = 0; i <= LIST_LENGTH; ++i) {
        list_append(list, &i);
    }

    list_t *mapped = list_map(list, f);

    for (int i = LIST_LENGTH; i >= LIST_LENGTH - 2; --i) {
        list_pop_last(list, &test);
        ASSERT_RETURN(test == i, 1);
        list_pop_last(mapped, &test);
        ASSERT_RETURN(test == i + 1, 1);
    }

    int wait;

    list_reverse(list);
    list_sort(list);

    list_pop(list, 2, &test);
    ASSERT_RETURN(test == 2, 1);

    list_free(list);

    printf("%sTEST: list_t.c : ALL TESTS PASSED SUCCESSFULLY !\n", KGRN);

    return 0;
}


