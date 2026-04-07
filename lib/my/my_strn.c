/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_strn
*/

#include "my.h"

int word_in(char *str, char *word)
{
    int i = 0;

    for (; word[i]; i++)
        if (word[i] != str[i])
            break;
    if (word[i] != 0)
        return 0;
    return i;
}

int my_strn(char *str, char *ind)
{
    int i = 0;
    int res = 0;

    if (!str || !ind)
        return 0;
    for (i = 0; str[i]; i++) {
        res = word_in(str + i, ind);
        if (res != 0)
            return res + i;
    }
    return 0;
}
