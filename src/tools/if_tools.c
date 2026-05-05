/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if_tools
*/

#include "../../include/struct.h"

int child(tcsh_t *term, int fd[2], char *cond)
{
    int pid = fork();
    char **env = node_to_array(term->env);
    int res = 0;

    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(STDERR_FILENO);
        close(fd[1]);
        execve("/usr/bin/calc", (char *[]){"calc", cond, NULL}, env);
        exit(-1);
    }
    waitpid(pid, &res, 0);
    if (env)
        free(env);
    if (!WIFEXITED(res) || WEXITSTATUS(res) != 0)
        return my_cmd_error(": Expression Syntax.\n", "if", ALTERNATIVE_EXIT);
    return SUCCESS_EXIT;
}
