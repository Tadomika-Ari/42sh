/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if
*/

#include <unistd.h>
#include "../../include/struct.h"

static char *get_fd(int fd)
{
    struct stat file_stat = {0};
    char *buffer = NULL;

    if (fstat(fd, &file_stat) == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (file_stat.st_size + 1));
    if (fd == -1 || !buffer || read(fd, buffer, file_stat.st_size) == -1) {
        if (buffer)
            free(buffer);
        return NULL;
    }
    buffer[file_stat.st_size] = 0;
    return buffer;
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
    int fd = 1;
    int res = 0;

    if (!argv || len_array(argv) < 3 || socket
        (AF_UNIX, SOCK_STREAM, fd) == -1) {
        *error = true;
        if (fd != 1)
            close(fd);
        return ALTERNATIVE_EXIT;
    }
    term->fd[0] = STDIN_FILENO;
    term->fd[1] = fd;
    if (search_command(term, (char*[]){"calc", argv[1]}, NULL) != 0) {
        *error = true;
        close(fd);
        return ALTERNATIVE_EXIT;
    }
    res = true_cond(fd, error);
    close(fd);
    return res;
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

static int exec_if(tcsh_t *term, char **argv)
{
    return search_command(term, argv + 2, NULL);
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
        return exec_if(term, argv);
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

    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if ((cond != 0 && then == 1) || (cond == 0 && then == 0))
        return SUCCESS_EXIT;
    if (cond != 0 && then == 0)
        return exec_if(term, argv);
    return in_if(term);
}
