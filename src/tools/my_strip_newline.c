/*
** EPITECH PROJECT, 2026
** my_strip_newline
** File description:
** Remove trailing newline from string
*/

#include "../../include/struct.h"

char *my_strip_newline(char *str)
{
    size_t len = 0;

    if (!str)
        return NULL;
    len = my_strlen(str);
    if (len > 0 && str[len - 1] == '\n')
        str[len - 1] = '\0';
    return str;
}
