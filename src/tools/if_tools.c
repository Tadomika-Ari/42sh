/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if_tools
*/

#include "../../include/struct.h"

int my_err(bool *error, int out)
{
    *error = true;
    return out;
}

static int in_child(tcsh_t *term, int fd[2], int in[2])
{
    char **env = node_to_array(term->env);
    char *path = search_bin(term, "bc");

    close(in[1]);
    dup2(in[0], STDIN_FILENO);
    close(in[0]);
    close(fd[0]);
    dup2(fd[1], STDOUT_FILENO);
    dup2(fd[1], STDERR_FILENO);
    close(fd[1]);
    execve(path, (char *[]){"bc", "-q", NULL}, env);
    free(env);
    free(path);
    exit(-1);
}

static int child_cond(tcsh_t *term, int fd[2], char *cond)
{
    int pid = 0;
    int in[2] = {-1, -1};
    int res = 0;

    if (pipe(in) != SUCCESS_EXIT)
        return ALT_EXIT;
    pid = fork();
    if (pid == 0)
        in_child(term, fd, in);
    close(in[0]);
    write(in[1], cond, strlen(cond));
    write(in[1], "\n", 1);
    close(in[1]);
    waitpid(pid, &res, 0);
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
            return ALT_EXIT;
    return SUCCESS_EXIT;
}

char *read_fd(int pipefd[2])
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

static int is_numeric_output(const char *str)
{
    if (str == NULL || str[0] == '\0')
        return ALT_EXIT;
    for (int i = 0; str[i] != '\0'; i++) {
        if ((str[i] >= '0' && str[i] <= '9') || str[i] == ' ' ||
            str[i] == '\n' || str[i] == '\t' || str[i] == '-')
            continue;
        return ALT_EXIT;
    }
    return SUCCESS_EXIT;
}

int fallback_cond(tcsh_t *term, char *cond, bool *error)
{
    int pipefd[2] = {-1, -1};
    int result = 0;
    char *tmp = NULL;

    if (pipe(pipefd) != SUCCESS_EXIT)
        return my_err(error, ALT_EXIT);
    if (child_cond(term, pipefd, cond) != SUCCESS_EXIT) {
        close(pipefd[0]);
        close(pipefd[1]);
        return my_err(error, ALT_EXIT);
    }
    tmp = read_fd(pipefd);
    if (is_numeric_output(tmp) != SUCCESS_EXIT) {
        free(tmp);
        return my_err(error, my_cmd_error(": Expression Syntax.\n", "if", -1));
    }
    result = tmp != NULL ? atoi(tmp) : 0;
    free(tmp);
    return result;
}
