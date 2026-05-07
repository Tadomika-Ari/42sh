/*
** EPITECH PROJECT, 2026
** fill
** File description:
** job
*/

#include "../../include/struct.h"

nodes_t *new_node(void *data)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    if (!new)
        return NULL;
    new->data = data;
    return new;
}

nodes_t *create_new_node(char *lign_env)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    if (!new)
        return NULL;
    new->data = my_strdup(lign_env);
    if (!new->data) {
        free(new);
        return NULL;
    }
    return new;
}
