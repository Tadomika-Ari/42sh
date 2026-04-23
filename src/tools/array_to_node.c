/*
** EPITECH PROJECT, 2026
** array
** File description:
** node
*/

#include "../../include/struct.h"

nodes_t *array_to_node(char **array)
{
    nodes_t *list = NULL;

    if (!array | !array[0])
        return NULL;
    for (int i = 0; array[i] != NULL; i++) {
        push_back(&list, create_new_node(array[i]));
    }
    return list;
}
