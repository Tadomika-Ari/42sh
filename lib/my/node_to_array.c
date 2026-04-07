/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** node_to_array
*/

#include "my.h"

char **node_to_array(nodes_t *head)
{
    int len = len_node(head);
    char **res = malloc(sizeof(char *) * (len + 1));
    nodes_t *tmp = head;

    for (int i = 0; i < len; i++) {
        res[i] = tmp->data;
        tmp = tmp->next;
    }
    res[len] = NULL;
    return res;
}
