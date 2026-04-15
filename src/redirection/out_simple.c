/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** right_simple
*/

#include "../../include/struct.h"

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
    result = my_strdup(tmp[len_array(tmp) - 1]);
    free_array(tmp);
    return result;
}

int double_out(char *argv)
{
    char *name = take_name(argv);
    int fd = STDOUT_FILENO;

    if (name == NULL)
        return -1;
    fd = open(name, O_WRONLY | O_CREAT | O_APPEND, 0644);
    free(name);
    return fd;
}

int search_out(char *argv)
{
    int begin = search_ind(argv, '>');
    char *file = NULL;

    if (begin == -1)
        return STDOUT_FILENO;
    for (int i = begin + 2; argv[i]; i++)
        if (argv[i] == '>')
            return -1;
    if (argv[begin + 1] == '>')
        return double_out(&argv[begin + 2]);
    file = take_name(&argv[begin + 1]);
    if (file == NULL)
        return -1;
    begin = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
    free(file);
    return begin;
}
