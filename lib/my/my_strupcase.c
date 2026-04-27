/*
** EPITECH PROJECT, 2025
** strupdcase
** File description:
** strupcase
*/

#include "my.h"

char *my_strupcase(char *str)
{
    if (!str)
        return NULL;
    for (int index = 0; str[index] != '\0'; index++) {
        if ('a' <= str[index] && str[index] <= 'z') {
            str[index] = str[index] - 32;
        }
    }
    return str;
}
