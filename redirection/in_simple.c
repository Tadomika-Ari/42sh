/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** in_simple
*/

#include "../include/struct.h"

int exist(char *str)
{
    int fd = open(str, O_RDONLY);

    if (fd == -1)
        return -1;
    close(fd);
    return 0;
}

static char *take_name(char *argv)
{
    char **tmp = NULL;
    char *result = crop(argv);

    if (!result)
        return NULL;
    tmp = my_str_to_word_array(result, " \n");
    free(result);
    if (tmp == NULL)
        return NULL;
    for (int i = 0; tmp[i]; i++) {
        if (exist(tmp[i]) == -1) {
            free_array(tmp);
            return NULL;
        }
    }
    result = my_strdup(tmp[len_array(tmp) - 1]);
    free_array(tmp);
    return result;
}

static char *take_cond(char *argv)
{
    char **tmp = NULL;
    char *result = crop(argv);

    if (!result)
        return NULL;
    tmp = my_str_to_word_array(result, " \n");
    free(result);
    if (tmp == NULL)
        return NULL;
    result = my_strdup(tmp[len_array(tmp) - 1]);
    free_array(tmp);
    return result;
}

void take_get(char *name, int fd[2])
{
    char *line = NULL;
    size_t len = 0;

    while (1) {
        write(1, "> ", 2);
        if (getline(&line, &len, stdin) == -1)
            break;
        line[my_strlen(line) - 1] = '\0';
        if (my_strcmp(line, name) == 0)
            break;
        write(fd[1], line, strlen(line));
        write(fd[1], "\n", 1);
    }
    free(line);
}

int double_in(char *argv)
{
    char *name = take_cond(argv);
    int fd[2] = {-1, -1};

    if (name == NULL)
        return -1;
    if (pipe(fd) == -1)
        return -1;
    take_get(name, fd);
    close(fd[1]);
    free(name);
    return fd[0];
}

int search_in(char *argv)
{
    int begin = search_ind(argv, '<');
    char *file = NULL;

    if (begin == -1)
        return STDIN_FILENO;
    for (int i = begin + 2; argv[i]; i++)
        if (argv[i] == '<')
            return -1;
    if (argv[begin + 1] == '<')
        return double_in(&argv[begin + 2]);
    file = take_name(&argv[begin + 1]);
    if (file == NULL)
        return -1;
    begin = open(file, O_RDONLY);
    free(file);
    return begin;
}
