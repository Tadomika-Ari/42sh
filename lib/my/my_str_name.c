/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_str_name
*/

#include "my.h"

int my_str_name(char *str)
{
    if (!str)
        return 0;
    for (int i = 0; str[i]; i++) {
        if ((str[i] < 'a' || str[i] > 'z') && (str[i] < 'A' || str[i] > 'Z')
            && (str[i] < '0' || str[i] > '9') && str[i] != '_')
            return 1;
    }
    return 0;
}
