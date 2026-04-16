/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** env
*/

#include "../../include/struct.h"

int env(tcsh_t *term, char **argv)
{
    if (len_array(argv) > 0)
        return error_too_many_argument("env");
    for (nodes_t *tmp = term->env; tmp; tmp = tmp->next) {
        if (term->pipe_fd[1] != -1 || term->last != true) {
            write(term->pipe_fd[1], tmp->data, my_strlen(tmp->data));
            write(term->pipe_fd[1], "\n", 1);
        } else {
            write(1, tmp->data, my_strlen(tmp->data));
            write(1, "\n", 1);
        }
    }
    return SUCCESS_EXIT;
}
