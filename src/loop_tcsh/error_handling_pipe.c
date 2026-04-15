/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** error_handling_pipe
*/

#include "../../include/struct.h"

void delete_red(char **cmd)
{
    int len = len_array(cmd);

    for (int i = 0; cmd[0][i]; i++)
        if (cmd[0][i] == '<' || cmd[0][i] == '>')
            cmd[0][i] = '\0';
    if (len == 1)
        return;
    for (int i = 0; cmd[len - 1][i]; i++)
        if (cmd[len - 1][i] == '>')
            cmd[len - 1][i] = '\0';
}

int reinit(tcsh_t *term, char *cmd, char **cmd_pipe)
{
    term->fd[0] = -1;
    term->fd[1] = -1;
    term->pipe_fd[0] = -1;
    term->pipe_fd[1] = -1;
    term->first = true;
    term->last = false;
    term->prev = -1;
    term->fd[0] = search_in(cmd);
    term->fd[1] = search_out(cmd);
    if (term->fd[0] == -1 || term->fd[1] == -1) {
        if (term->fd[0] != -1 && term->fd[0] != STDIN_FILENO)
            close(term->fd[0]);
        if (term->fd[1] != -1 && term->fd[1] != STDOUT_FILENO)
            close(term->fd[1]);
        return error_ambigious();
    }
    delete_red(cmd_pipe);
    return SUCCESS_EXIT;
}

int red_in_pipe(char *cmd)
{
    for (int j = 0; cmd[j]; j++)
        if (cmd[j] == '<' || cmd[j] == '>')
            return FAILURE_EXIT;
    return SUCCESS_EXIT;
}

int correct_lign(char *cmd, char **cmd_pipe)
{
    int id = 0;

    for (int i = 0; cmd[i]; i++) {
        if (cmd[i] == '|')
            id++;
        if (cmd_pipe[id] == NULL)
            return error_null();
    }
    return SUCCESS_EXIT;
}

int correct_type(char **cmd)
{
    int mid = 1;

    if (!cmd || !cmd[0])
        return error_null();
    if (len_array(cmd) == 1)
        return SUCCESS_EXIT;
    for (int i = 0; cmd[0][i]; i++)
        if (cmd[0][i] == '>')
            return error_ambigious();
    for (; cmd[mid]; mid++) {
        if (!cmd[mid + 1])
            break;
        if (red_in_pipe(cmd[mid]) != 0)
            return error_ambigious();
    }
    for (int i = 0; cmd[mid][i]; i++)
        if (cmd[mid][i] == '<')
            return error_ambigious();
    return SUCCESS_EXIT;
}
