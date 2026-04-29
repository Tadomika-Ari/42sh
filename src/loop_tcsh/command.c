/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** command
*/

#include "../../include/struct.h"

static void close_if_valid(int *fd)
{
    if (*fd >= 0) {
        close(*fd);
        *fd = -1;
    }
}

int search_command(tcsh_t *term, char **command, char *cmd)
{
    nodes_t *path = search_node(term->env, "PATH");
    char **bin = NULL;
    char *lign = NULL;

    if (!path)
        bin = my_str_to_word_array("/usr/bin:/bin:/usr/local/bin", ":=\n");
    else
        bin = my_str_to_word_array(path->data, ":=\n");
    if (!bin)
        return command_not_found(command[0]);
    for (int i = 0; bin[i]; i++) {
        lign = search_binary(bin[i], command[0]);
        if (lign != NULL) {
            free_array(bin);
            return exec(lign, command, term, cmd);
        }
    }
    free_array(bin);
    return -1;
}

static int normalize(tcsh_t *term, char *cmd, char **command, int status)
{
    if (status == -1)
        status = exec(my_strdup(command[0]), command, term, cmd);
    if (status == -1)
        command_not_found(command[0]);
    if (status == 1) {
        free_array(command);
        return -1;
    }
    free_array(command);
    return status;
}

static int apply_command(tcsh_t *term, char *cmd)
{
    char **command = sweeper(term, cmd);
    int status = 0;

    if (!command)
        return SUCCESS_EXIT;
    for (nodes_t *tmp = term->func; tmp; tmp = tmp->next)
        if (my_strcmp(command[0], ((function_t *)tmp->data)->name) == 0)
            return execute(tmp, command, term);
    status = search_command(term, command, cmd);
    if (status == -1)
        status = sepecial_variable(term, cmd);
    return normalize(term, cmd, command, status);
}

static void pipe_in(tcsh_t *term, int *pipe_fd, char **cmd_pipe)
{
    int next_pipe[2] = {-1, -1};

    for (int i = 0; cmd_pipe[i]; i++) {
        term->last = !cmd_pipe[i + 1] ? true : false;
        term->first = i != 0 ? false : true;
        if (!term->last && pipe(next_pipe) == -1) {
            close_if_valid(&term->prev);
            break;
        }
        term->pipe_fd[0] = term->prev;
        term->pipe_fd[1] = term->last ? -1 : next_pipe[1];
        pipe_fd[i] = apply_command(term, cmd_pipe[i]);
        if (!term->last)
            close_if_valid(&next_pipe[1]);
        close_if_valid(&term->prev);
        term->prev = term->last ? -1 : next_pipe[0];
    }
}

static void algo(int *pipe_fd, int *value, int count)
{
    for (int i = 0; i != count; i++) {
        waitpid(pipe_fd[i], value, 0);
        algo_exit(value);
        if (pipe_fd[i] == -1)
            *value = 1;
        *value = *value == -1 ? 1 : *value;
    }
}

int do_pipe(tcsh_t *term, int *pipe_fd, int count, char **cmd_pipe)
{
    int value = 0;

    pipe_in(term, pipe_fd, cmd_pipe);
    if (term->prev != -1)
        close(term->prev);
    if (!term->is_background)
        algo(pipe_fd, &value, count);
    free(pipe_fd);
    free_array(cmd_pipe);
    if (term->fd[0] != -1 && term->fd[0] != STDIN_FILENO)
        close(term->fd[0]);
    if (term->fd[1] != -1 && term->fd[1] != STDOUT_FILENO)
        close(term->fd[1]);
    return value;
}

static bool has_background_operator(tcsh_t *term, char *cmd)
{
    char **parts = sweeper(term, cmd);
    int len = 0;
    bool result = false;

    if (!parts)
        return false;
    len = len_array(parts);
    if (len > 0 && my_strcmp(parts[len - 1], "&") == 0)
        result = true;
    free_array(parts);
    return result;
}

static void reset_pipefd(int *pipe_fd, int count
    , tcsh_t *term, bool is_background)
{
    for (int i = 0; i != count; i++)
        pipe_fd[i] = -1;
    term->is_background = is_background;
}

int choose_command(tcsh_t *term, char *cmd)
{
    char **cmd_pipe = my_str_to_word_array(cmd, "|\n");
    int *pipe_fd = NULL;
    int count = 0;
    bool is_background = false;

    if (correct_type(cmd_pipe) != 0 || correct_lign(cmd, cmd_pipe) != 0)
        return 1;
    is_background = has_background_operator(term, cmd);
    if (reinit(term, cmd, cmd_pipe) != 0) {
        free_array(cmd_pipe);
        return ALTERNATIVE_EXIT;
    }
    count = len_array(cmd_pipe);
    pipe_fd = malloc(sizeof(int) * count);
    if (pipe_fd == NULL) {
        free_array(cmd_pipe);
        return FAILURE_EXIT;
    }
    reset_pipefd(pipe_fd, count, term, is_background);
    return do_pipe(term, pipe_fd, count, cmd_pipe);
}
