/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** push_back
*/

#include "my.h"

void push_back(nodes_t **old, nodes_t *new)
{
    nodes_t *new_node = NULL;

    if (*old == NULL) {
        *old = new;
        new->next = NULL;
        return;
    }
    for (new_node = *old; new_node->next != NULL; new_node = new_node->next);
    new_node->next = new;
    new->next = NULL;
}
