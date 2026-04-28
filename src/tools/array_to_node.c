/*
** EPITECH PROJECT, 2026
** array
** File description:
** node
*/

#include "../../include/struct.h"

static void free_nodes(nodes_t *list)
{
    nodes_t *next = NULL;

    for (nodes_t *current = list; current; current = next) {
        next = current->next;
        free(current->data);
        free(current);
    }
}

nodes_t *array_to_node(char **array)
{
    nodes_t *list = NULL;
    nodes_t *node = NULL;
    char *dup = NULL;

    if (!array || !array[0])
        return NULL;
    for (int i = 0; array[i] != NULL; i++) {
        dup = my_strdup(array[i]);
        if (!dup) {
            free_nodes(list);
            return NULL;
        }
        node = create_new_node(dup);
        if (!node) {
            free(dup);
            free_nodes(list);
            return NULL;
        }
        push_back(&list, node);
    }
    return list;
}
