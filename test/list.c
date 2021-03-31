//
// Created by LEO on 2021-03-31.
//

#include "../include/list.h"
#include "../include/utils.h"

#define KGRN  "\x1B[32m"
#define LIST_LENGTH 1000

#include <string.h>
#include <stdlib.h>
#include <stdio.h>

int compare(void *a, void *b)
{
    return *(int *)a > *(int *)b;
}

void print(void *data)
{
    printf("%d\n", *(int *)data);
}

int main(int argc, char **argv)
{
    list_t *list = list_create(LIST_LENGTH, sizeof(int));
    list->compare = compare;

    int buf;

    for (int i = 0; i < list->length; ++i)
        list_insert(list, i, &i);

    list_t *copy = list_copy(list);
    int buf_copy;

    for (int i = 0; i < list->length; ++i) {
        list_peek(list, i, &buf);
        list_peek(copy, i, &buf_copy);
        ASSERT_RETURN(buf == i, 1);
        ASSERT_RETURN(buf == buf_copy, 1);
    }

    list_reverse(list);
    for (int i = 0; i < list->length; ++i) {
        list_peek(list, i, &buf);
        ASSERT_RETURN(buf == LIST_LENGTH - i - 1, 1);
    }

    list_sort(list);
    for (int i = 0; i < list->length; ++i) {
        list_peek(list, i, &buf);
        ASSERT_RETURN(buf == i, 1);
    }

    list_free(list);
    list_free(copy);

    printf("%sTEST: list_t.c : ALL TESTS PASSED SUCCESSFULLY !\n", KGRN);

    return 0;
}


