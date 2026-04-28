/*
** EPITECH PROJECT, 2026
** translate
** File description:
** trnaslate
*/

#include "../../include/struct.h"
#include <string.h>

char **solo_tab(char *str)
{
    char **tab = malloc(sizeof(char *) * (1 + 1));

    if (!tab)
        return NULL;
    tab[0] = strndup(&str[1], my_strlen(str) - 2);
    tab[1] = NULL;
    return tab;
}

char **translate(char *str)
{
    char **res = NULL;

    if (is_inihbitor(str) == TRUE)
        return solo_tab(str);
    res = my_str_to_word_array(str, " ");
    return res;
}
