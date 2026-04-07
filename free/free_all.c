/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** free_all
*/

#include "../include/struct.h"

void free_node(nodes_t *head)
{
    nodes_t *forward = NULL;

    if (!head)
        return;
    forward = head;
    while (head != NULL) {
        forward = forward->next;
        if (head->data)
            free(head->data);
        free(head);
        head = forward;
    }
}

void free_all(tcsh_t *term)
{
    if (!term)
        return;
    free_node(term->env);
    free_node(term->func);
    if (term->old)
        free(term->old);
    free(term);
}
