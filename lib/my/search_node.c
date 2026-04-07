/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** search_node
*/

#include "my.h"

nodes_t *search_node(nodes_t *head, char *cdt)
{
    nodes_t *tmp = NULL;

    for (tmp = head; tmp; tmp = tmp->next)
        if (my_strcmp(tmp->data, cdt) == 0)
            return tmp;
    return NULL;
}
