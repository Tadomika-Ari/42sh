/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** len_node
*/

#include "my.h"

int len_node(nodes_t *head)
{
    int len = 0;

    for (nodes_t *node = head; node; node = node->next)
        len++;
    return len;
}
