/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if
*/

#include <unistd.h>
#include "../../include/struct.h"

static int fallback_cond(char *expr)
{
    int left = 0;
    int right = 0;

    if (expr && sscanf(expr, " ( %d == %d ) ", &left, &right) == 2)
        return left == right;
    if (expr && sscanf(expr, "(%d==%d)", &left, &right) == 2)
        return left == right;
    return 0;
}

static char *search_buff(int fd, char *buff, char *tmp)
{
    char *new_buff = NULL;

    for (int i = 0; read(fd, tmp, 1) > 0; i++) {
        new_buff = realloc(buff, i + 2);
        if (new_buff == NULL) {
            free(buff);
            free(tmp);
            return NULL;
        }
        buff = new_buff;
        buff[i] = tmp[0];
        buff[i + 1] = '\0';
    }
    free(tmp);
    return buff;
}

static char *get_fd(int fd)
{
    char *buff = malloc(sizeof(char) * 1);
    char *tmp = malloc(sizeof(char) * 1);

    if (buff == NULL || tmp == NULL) {
        free(buff);
        free(tmp);
        return NULL;
    }
    buff[0] = '\0';
    return search_buff(fd, buff, tmp);
}

static int true_cond(int fd, bool *error)
{
    char *cond = get_fd(fd);
    int res = 0;

    if (cond == NULL) {
        *error = true;
        return ALTERNATIVE_EXIT;
    }
    res = atoi(cond);
    free(cond);
    return res;
}

static int search_condition(tcsh_t *term, char **argv, bool *error)
{
    int pid = fork();
    int status = 0;
    int fd[2] = {-1, -1};

    pipe(fd);
    if (pid == 0) {
        dup2(fd[1], STDOUT_FILENO);
        dup2(fd[1], STDERR_FILENO);
        close(fd[0]);
        close(fd[1]);
        execve("/bin/calc", (char *[]){"calc", argv[0], NULL},
            node_to_array(term->env));
        _exit(1);
    }
    close(fd[1]);
    if (waitpid(pid, &status, 0) < 0) {
        *error = true;
        return ALTERNATIVE_EXIT;
    }
    return true_cond(fd[0], error);
}

static int is_then(char **argv)
{
    int res = 0;

    if (argv == NULL)
        return res;
    for (int i = 0; argv[i]; i++) {
        if (my_strcmp(argv[i], "then") == 0 && argv[i + 1] == NULL) {
            res = 1;
            return res;
        }
        if (my_strcmp(argv[i], "then") == 0 && argv[i + 1] != NULL) {
            res = -1;
            return res;
        }
    }
    return res;
}

static int stop(char **argv)
{
    if (my_strcmp("else", argv[0]) == 0) {
        if (argv[1] == NULL)
            return SUCCESS_EXIT;
        return ALTERNATIVE_EXIT;
    }
    if (my_strcmp("endif", argv[0]) == 0)
        return SUCCESS_EXIT;
    return ALTERNATIVE_EXIT;
}

int else_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if ((cond != 0 && then == 1) || (cond == 0 && then == 0))
        return SUCCESS_EXIT;
    if (cond != 0 && then == 0)
        return search_command(term, argv + 1, NULL);
    return ALTERNATIVE_EXIT;
}

int in_if(tcsh_t *term)
{
    size_t len = 0;
    char *lign = NULL;
    char **tmp = NULL;

    while (1) {
        if (getline(&lign, &len, stdin) == -1) {
            free(lign);
            return ALTERNATIVE_EXIT;
        }
        tmp = my_str_to_word_array(lign, " ");
        if (stop(tmp) == 0) {
            free_array(tmp);
            return SUCCESS_EXIT;
        }
        if (else_if(term, tmp) != 0) {
            free_array(tmp);
            return SUCCESS_EXIT;
        }
        free_array(tmp);
    }
}

int my_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (cond == 0)
        cond = fallback_cond(argv[0]);
    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if (cond != 0 && then == 0 && argv[1] != NULL)
        return search_command(term, argv + 1, NULL);
    if ((cond != 0 && then == 1) || (cond == 0 && then == 0))
        return SUCCESS_EXIT;
    return in_if(term);
}
