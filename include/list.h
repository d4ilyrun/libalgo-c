//
// Created by leo on 3/25/21.
//

#ifndef LIBALGO_LIST_H
#define LIBALGO_LIST_H

#include <stdlib.h>

#include "data_types.h"

typedef struct node_t_ {
    void *data;
    struct node_t_ *next;
    struct node_t_ *prev;
}node_t;

node_t  *node_create(void *data, Type type);
void    *node_get(node_t *node, Type type, void *out);

/**
 * <br>A generic linked list implementation.
 * <br>May not be the fastest but is quite easy to use.
 */
typedef struct list_t_ {
    Type type;
    size_t length;
    node_t *head;
    node_t *tail;

    void (*free) (void *);
    int (*compare) (void *, void *);
}list_t;

list_t  *list_create(size_t size_of_type);
node_t  *list_append(list_t *list, void *data);
node_t  *list_insert(list_t *list, int index, void *data);
void    *list_pop(list_t *list, int index, void *out);
void    *list_pop_last(list_t *list, void *out);
void     list_foreach(list_t *list, void (*f)(void *));
list_t  *list_map(list_t *list, void (*f)(void *));
node_t  *list_node_at_index(list_t *list, size_t index);
void    *list_index(list_t *list, size_t index);
void     list_free(list_t *list);
void     list_sort(list_t *list);
void     list_reverse(list_t *list);

#endif //LIBALGO_LIST_H
