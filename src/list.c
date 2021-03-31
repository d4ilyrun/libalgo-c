//
// Created by LEO on 2021-03-31.
//

#include "../include/list.h"
#include "../include/utils.h"

#include <string.h>

static int default_compare(void *, void *);

list_t *list_create(size_t len, size_t size_of_type)
{
    list_t *list = malloc(sizeof (list_t));
    list->length = len;
    list->type = data_type(size_of_type);
    list->list = malloc(len * size_of_type);
    list->compare = default_compare;

    return list;
}

void *list_insert(list_t *list, size_t index, void *data)
{
    ASSERT_RETURN(index < list->length, NULL);

    void *data_at_index = list->list + (index * list->type.size);
    memcpy(data_at_index, data, list->type.size);

    return data_at_index;
}

void *list_peek(list_t *list, size_t index, void *out)
{
    ASSERT_RETURN(index < list->length, NULL);
    void *data_at_index = list->list + (index * list->type.size);

    if (out)
        memcpy(out, data_at_index, list->type.size);
    return data_at_index;
}

void list_foreach(list_t *list, void (*f)(void *))
{
    void *p_list = list->list;

    for (size_t i = 0; i < list->length; ++i) {
        f(p_list);
        p_list += list->type.size;
    }
}

list_t *list_map(list_t *list, void (*f)(void *))
{
    list_t *mapped = list_create(list->length, list->type.size);
    void *p_list = list->list, *p_mapped = mapped->list;

    for (size_t i = 0; i < list->length; ++i) {
        memcpy(p_mapped, p_list, list->type.size);
        f(p_mapped);
        p_mapped += list->type.size;
        p_list += list->type.size;
    }

    mapped->compare = list->compare;
    mapped->free = list->free;

    return mapped;
}

void list_free(list_t *list)
{
    if (list->free) {
        void *p_list = list->list;

        for (size_t i = 0; i < list->length; ++i) {
            list->free(p_list);
            p_list += list->type.size;
        }
    }

    free(list->list);
}

void swap_ptr(void *a, void *b, void *tmp, size_t size) {
    memcpy(tmp, a,size);
    memcpy(a, b, size);
    memcpy(b, tmp, size);
}

void list_reverse(list_t *list)
{
    void *p_start = list->list;
    void *p_end = p_start + list->type.size * (list->length - 1) ;
    void *tmp = malloc(list->type.size);

    for (size_t i = 0; i < list->length / 2; ++i) {
        swap_ptr(p_start, p_end, tmp, list->type.size);
        p_start += list->type.size;
        p_end -= list->type.size;
    }

    free(tmp);
}

void list_sort(list_t *list)
{
    bool sorted = false;
    int start = 0, end = list->length - 1;
    void *tmp = malloc(list->type.size);
    void *p_list;

    while (!sorted && start <= end){
        sorted = true;
        p_list = list->list + start * list->type.size;
        for (int i = start; i < end; ++i) {
            if (list->compare(p_list, p_list + list->type.size)) {
                swap_ptr(p_list, p_list + list->type.size, tmp, list->type.size);
                sorted = false;
            }
            p_list += list->type.size;
        }
        end -= 1;
        for (int i = end; i >= start; --i) {
            if (list->compare(p_list - list->type.size, p_list)) {
                swap_ptr(p_list - list->type.size, p_list, tmp, list->type.size);
                sorted = false;
            }
            p_list -= list->type.size;
        }
        start += 1;
    }
}

list_t *list_copy(list_t *list)
{
    list_t *copy = malloc(sizeof (list_t));
    *copy = *list;

    copy->list = malloc(list->length * list->type.size);
    memcpy(copy->list, list->list, list->length * list->type.size);

    return copy;
}

static int default_compare(void *a, void *b)
{
    fprintf(stderr, "ERROR: trying to compare element of a l_list_t "
                    "without properly setting a comparing function first.\n");
    return FALSE;
}

