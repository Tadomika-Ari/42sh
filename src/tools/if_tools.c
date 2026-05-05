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

int join_len_until_then(char **argv)
{
    int len = 0;

    if (argv == NULL)
        return 0;
    for (int i = 0; argv[i] != NULL && my_strcmp(argv[i], "then") != 0; i++)
        len += strlen(argv[i]) + 1;
    return len;
}

int not_cond(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
        if ((str[i] > '9' || str[i] < '0') && str[i] != '=' && str[i] != '!'
            && str[i] != '|' && str[i] != '&' && str[i] != '>'
            && str[i] != '<' && str[i] != ')' && str[i] != '(' &&
            str[i] != '+' && str[i] != '-' && str[i] != '*' && str[i] != ' ')
            return ALTERNATIVE_EXIT;
    return SUCCESS_EXIT;
}

static char *read_fd(int pipefd[2])
{
    char buf[1024];
    ssize_t n = read(pipefd[0], buf, sizeof(buf) - 1);

    close(pipefd[1]);
    if (n < 1)
        return NULL;
    close(pipefd[0]);
    buf[n] = '\0';
    return my_strdup(buf);
}

int fallback_cond(tcsh_t *term, char *cond, bool *error)
{
    int pipefd[2] = {-1, -1};
    int result = 0;
    char *tmp = NULL;

    if (pipe(pipefd) != SUCCESS_EXIT) {
        *error = true;
        return ALTERNATIVE_EXIT;
    }
    if (child(term, pipefd, cond) != SUCCESS_EXIT) {
        close(pipefd[0]);
        close(pipefd[1]);
        *error = true;
        return ALTERNATIVE_EXIT;
    }
    tmp = read_fd(pipefd);
    result = tmp != NULL ? atoi(tmp) : 0;
    free(tmp);
    return result;
}
