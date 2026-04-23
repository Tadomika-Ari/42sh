/*
** EPITECH PROJECT, 2026
** check
** File description:
** str
*/

#include "../../include/struct.h"

int is_inihbitor(char *str)
{
    int len = my_strlen(str);
    char *tmp = NULL;

    if (str[0] == '\'' && str[0] == str[len - 1]) {
        return TRUE;
    }
    return FALSE;
}

int is_parenthesis(char *str)
{
    int len = my_strlen(str);

    if (str[0] == '(' && ')' == str[len - 1]) {
        return TRUE;
    }
    return FALSE;
}
