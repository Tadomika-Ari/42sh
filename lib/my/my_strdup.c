/*
** EPITECH PROJECT, 2025
** str dup
** File description:
** return a str modify with the parameter given
*/

#include "my.h"
#include <stdlib.h>

char *my_strdup(char const *src)
{
    char *str = NULL;

    if (!src)
        return NULL;
    str = malloc(sizeof(char) * (my_strlen(src) + 1));
    if (!str)
        return NULL;
    for (int i = 0; i <= my_strlen(src); i++)
        str[i] = src[i];
    return (str);
}
