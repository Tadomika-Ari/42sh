/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** compose_str
*/

#include "my.h"

int total_len(char *sep, char **argv)
{
    int res = 0;
    int len = my_strlen(sep);

    for (int i = 0; argv[i]; i++) {
        res += len;
        res += my_strlen(argv[i]);
    }
    return res;
}

char *assembling(char *base, char *sep, char **argv)
{
    char *result = malloc(sizeof(char) *
        (my_strlen(base) + total_len(sep, argv) + 1));
    int i = 0;

    if (!result)
        return NULL;
    result[0] = 0;
    my_strcat(result, base);
    for (i = 0; argv[i]; i++) {
        my_strcat(result, sep);
        my_strcat(result, argv[i]);
    }
    return result;
}
