/*
** EPITECH PROJECT, 2026
** check
** File description:
** quote
*/

#include "../../include/struct.h"

int check_quote(char *str)
{
    int len = my_strlen(str);

    if (len > 2 && (str[0] == '\"' && str[len - 1] != str[0]))
        return TRUE;
    if (len > 2 && (str[len - 1] == '\"' && str[len - 1] != str[0]))
        return TRUE;
    return FALSE;
}
