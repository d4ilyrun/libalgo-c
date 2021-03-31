//
// Created by leo on 3/25/21.
//

#include "../include/list.h"
#include "../include/utils.h"

#include <string.h>

static void default_free(void *);
static int default_compare(void *, void *);

/**
 * <br>Create an empty list
 * @param size_of_type
 * @return the new list's address
 */
l_list_t *l_list_create(size_t size_of_type)
{
    ASSERT_RETURN(size_of_type > 0, NULL);

    Type type = data_type(size_of_type);
    l_list_t *new_list = malloc(sizeof(l_list_t));

    *new_list = (l_list_t) {
        .type = type,
        .length = 0,
        .head = NULL,
        .tail = NULL,
        .free = default_free,
        .compare = default_compare
    };

    return new_list;
}

/**
 * <br>Append data at the end of a list.
 * @param list
 * @param data
 * @return the address of the node containing the new data
 */
node_t *l_list_append(l_list_t *list, void *data)
{
    node_t *node = node_create(data, list->type);

    if (!list->length)
        list->head = node;
    else {
        node->prev = list->tail;
        list->tail->next = node;
    }

    list->tail = node;
    list->length += 1;

    return node;
}

/**
 * <br>Insert data at a given index at the end of a list.
 * @param list
 * @param index
 * @param data
 * @return the address of the node containing the new data
 */
node_t *l_list_insert(l_list_t *list, int index, void *data)
{
    if (index == list->length)
        return l_list_append(list, data);

    node_t *data_node = node_create(data, list->type);

    if (!index) {
        data_node->next = list->head;
        list->head = data_node;
    } else {
        node_t *node = l_list_node_at_index(list, index);
        if (node->prev)
            node->prev->next = data_node;
        data_node->prev = node->prev;
        node->prev = data_node;
    }

    list->length += 1;
    return data_node;
}

/**
 * <br>Create a new node containing a data of type 'type'
 * @param data
 * @param type
 * @return the address of the created node
 */
node_t *node_create(void *data, Type type)
{
    node_t *node = malloc(sizeof(node_t));
    *node = (node_t) {
        .data = malloc(type.size),
        .next = NULL,
        .prev = NULL
    };

    memcpy(node->data, data, type.size);

    return node;
}

/**
 * <br>Retrieve data from a node.
 * @param node
 * @param type
 * @param out pointer storing the output value. A new memory space will be allocated if NULL.
 * @return the output address
 */
void *node_get(node_t *node, Type type, void *out)
{
    if (out == NULL)
        out = malloc(type.size);
    memcpy(out, node->data, type.size);

    return out;
}

/**
 * <br>Pops a data at a given index from a list.
 * @param list
 * @param index
 * @param out pointer storing the output value. A new memory space will be allocated if NULL.
 * @return the output address
 */
void *l_list_pop(l_list_t *list, int index, void *out)
{
    node_t *node = l_list_node_at_index(list, index);

    if (!node)
        return NULL;

    // if no next node : node was the list's tail
    if (!node->next)
        list->tail = node->prev;
    else
        node->next->prev = node->prev;

    // if no prev node : node was the list's head
    if (!node->prev)
        list->head = node->next;
    else
        node->prev->next = node->next;

    node_get(node, list->type, out);
    free(node);

    list->length -= 1;
    return out;
}

/**
 * <br>Pops the last value of a list.
 * @param list
 * @param out pointer storing the output value. A new memory space will be allocated if NULL.
 * @return the output address
 */
void *l_list_pop_last(l_list_t *list, void *out)
{
    return l_list_pop(list, list->length - 1, out);
}

/**
 * <br>Applies given function to every data in the list.
 * @param list
 * @param f
 */
void l_list_foreach(l_list_t *list, void (*f)(void *))
{
    for (node_t *node = list->head; node != NULL; node = node->next) {
        f(node->data);
    }
}

/**
 * <br>Create a new list containing the result of a function for every data of the original list.
 * @param list
 * @param f
 * @return the address of the newly created list
 */
l_list_t *l_list_map(l_list_t *list, void (*f)(void *))
{
    l_list_t *mapped = l_list_create(list->type.size);

    for (node_t *node = list->head; node != NULL; node = node->next) {
        l_list_append(mapped, node->data);
        f(mapped->tail->data);
    }

    mapped->type = list->type;
    mapped->free = list->free;
    mapped->compare = list->compare;

    return mapped;
}

/**
 * <br>Free an entire list
 * @param list
 */
void l_list_free(l_list_t *list)
{
    node_t *node = list->head;
    node_t *tmp = NULL;

    while (node != NULL) {
        tmp = node;
        node = node->next;
        list->free(tmp->data);
        free(tmp);
    }

    list->head = NULL;
    list->tail = NULL;
    free(list);
}

/**
 * <br> Return the data at a given index on a list.
 * <br> Similar to `list_pop` but the data will not be removed from the list.
 * @param list
 * @param index
 * @return the original data pointer
 */
void *l_list_index(l_list_t *list, size_t index)
{
    node_t *node = l_list_node_at_index(list, index);

    return node ? node->data : NULL;
}

/**
 * <br> Return the node at a given index in a list
 * @param list
 * @param index
 * @return the original node pointer
 */
node_t *l_list_node_at_index(l_list_t *list, size_t index)
{
    ASSERT_RETURN(index >= 0, NULL);
    ASSERT_RETURN(index < list->length, NULL);

    node_t *node;

    if (index > list->length / 2) {
        node = list->tail;
        for (int i = list->length - 1; i > index; --i)
            node = node->prev;
        return node;
    }

    node = list->head;
    for (int i = 0; i < index; ++i)
        node = node->next;

    return node;
}

/**
 * <br> Sorts a list using a shaker-sort implementation
 * @param list
 */
void l_list_sort(l_list_t *list)
{
    int start = 0;
    int end = list->length - 1;
    bool sorted = false;
    node_t *node, *next;

    while (!sorted && end >= start) {
        sorted = true;
        node = l_list_node_at_index(list, start);
        for (int i = start; i < end; i++) {
            if (list->compare(node->data, node->next->data)) {
                SWAP(node->data, node->next->data);
                sorted = false;
            }
            node = node->next;
        }
        for (int i = --end; i >= start; --i) {
            if (list->compare(node->prev->data, node->data)) {
                SWAP(node->data, node->prev->data);
                sorted = false;
            }
            node = node->prev;
        }
        ++start;
    }
}

/**
 * <br> Reverse a list in place
 * @param list
 */
void l_list_reverse(l_list_t *list)
{
    node_t *a, *b;

    for (int i = 0; i < list->length / 2; ++i) {
        a = l_list_node_at_index(list, i);
        b = l_list_node_at_index(list, list->length - 1 - i);
        SWAP(a->data, b->data);
    }
}

static void default_free(void *data) { free(data); }

static int default_compare(void *a, void *b)
{
    fprintf(stderr, "ERROR: trying to compare element of a l_list_t "
                    "without properly setting a comparing function first.\n");
    return FALSE;
}
