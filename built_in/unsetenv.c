/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** unsetenv
*/

#include "../include/struct.h"

void in_list(nodes_t *last, char *argv)
{
    nodes_t *current = last->next;

    while (current) {
        if (my_strcmp(current->data, argv) == 0) {
            last->next = current->next;
            free(current->data);
            free(current);
            return;
        }
        current = current->next;
        last = last->next;
    }
}

void delete_in_list(nodes_t **head, char *argv)
{
    nodes_t *current = *head;

    if (my_strcmp(current->data, argv) == 0) {
        *head = current->next;
        free(current->data);
        free(current);
        return;
    }
    in_list(current, argv);
}

static int is_that_a_star(char *argv)
{
    for (int i = 0; argv[i]; i++)
        if (argv[i] == '*')
            return TRUE;
    return FALSE;
}

int my_unsetenv(tcsh_t *term, char **argv)
{
    if (len_array(argv) == 0)
        return error_not_enough_argument("unsetenv");
    for (int i = 0; argv[i]; i++)
        if (is_that_a_star(argv[i]) == TRUE)
            return argument_not_support("unsetenv");
    for (int i = 0; argv[i]; i++)
        delete_in_list(&term->env, argv[i]);
    return SUCCESS_EXIT;
}
