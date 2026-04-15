/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** child
*/

#include "../../include/struct.h"

static void signaled(int *result)
{
    if (WTERMSIG(*result) == SIGSEGV) {
        write(1, "Segmentation fault", 18);
        if (WCOREDUMP(*result))
            write(1, " (core dumped)", 14);
        write(1, "\n", 1);
        *result = 128 + WTERMSIG(*result);
        return;
    }
    if (WTERMSIG(*result) == SIGFPE) {
        write(1, "Floating exception", 19);
        if (WCOREDUMP(*result))
            write(1, " (core dumped)", 14);
        write(1, "\n", 1);
        *result = 128 + WTERMSIG(*result);
        return;
    }
    *result = -1;
}

void algo_exit(int *result)
{
    if (WIFEXITED(*result)) {
        *result = WEXITSTATUS(*result);
        return;
    }
    if (WIFSIGNALED(*result))
        signaled(result);
}

static int error_handling(char *bin, char **command, char **env)
{
    if (!command || !env)
        return my_free((void *[]){env}, 1, FAILURE_EXIT);
    if (is_it_directory(bin) != 0 ||
        (access(bin, X_OK) == -1 && access(bin, F_OK) == 0))
        return my_free((void *[]){bin, env}, 2,
            error_permission_denied(command[0]));
    if (access(bin, X_OK) == -1)
        return my_free((void *[]){bin, env}, 2, command_not_found(command[0]));
    return 0;
}

static int child_return(char *bin, char **command, tcsh_t *term, char **env)
{
    execve(bin, command, env);
    error_syntax(bin);
    my_free((void *[]){bin, env}, 2, 0);
    free_array(command);
    free_all(term);
    exit(1);
}

static int child(char *bin, char **command, tcsh_t *term, char **env)
{
    if (term->fd[0] >= 0 && term->fd[0] != STDIN_FILENO) {
        if (term->first == true)
            dup2(term->fd[0], STDIN_FILENO);
        close(term->fd[0]);
    }
    if (term->fd[1] >= 0 && term->fd[1] != STDOUT_FILENO) {
        if (term->last == true)
            dup2(term->fd[1], STDOUT_FILENO);
        close(term->fd[1]);
    }
    if (term->last == false)
        dup2(term->pipe_fd[1], STDOUT_FILENO);
    if (term->first == false)
        dup2(term->pipe_fd[0], STDIN_FILENO);
    if (term->pipe_fd[0] >= 0)
        close(term->pipe_fd[0]);
    if (term->pipe_fd[1] >= 0)
        close(term->pipe_fd[1]);
    return child_return(bin, command, term, env);
}

int exec(char *bin, char **command, tcsh_t *term, char *cmd)
{
    int pid = 0;
    char **env = node_to_array(term->env);
    int res = error_handling(bin, command, env);

    if (res != 0)
        return res;
    pid = fork();
    if (pid == 0) {
        free(cmd);
        return child(bin, command, term, env);
    }
    return my_free((void *[]){bin, env}, 2, pid);
}
