/*
** EPITECH PROJECT, 2026
** minishell2
** File description:
** right_simple
*/

#include "../../include/struct.h"

int search_ind(char *argv, char c)
{
    for (int i = 0; argv[i]; i++)
        if (argv[i] == c)
            return i;
    return -1;
}

char *crop(char *argv)
{
    int max = 0;
    char *result = NULL;

    for (int i = 0; argv[i] && argv[i] != '<' && argv[i] != '>' &&
        argv[i] != '|'; i++)
        max++;
    result = malloc(sizeof(char) * (max + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; i != max; i++)
        result[i] = argv[i];
    result[max] = '\0';
    return result;
}
