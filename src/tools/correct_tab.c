/*
** EPITECH PROJECT, 2026
** correct
** File description:
** tab
*/

#include "../../include/struct.h"

int unmatch_single(char *str)
{
    int len = my_strlen(str);

    if (str[0] == '\'' && str[len - 1] != '\''
        || str[0] != '\'' && str[len - 1] == '\'')
        return TRUE;
    return FALSE;
}

int check_element(char **tab, int i)
{
    if (unmatch_single(tab[i]) == TRUE)
        return put_err(UNMATCH_SINGLE);
    return TRUE;
}

void change(char **tab, int i)
{
    int len = my_strlen(tab[i]);
    char *tmp = NULL;

    if (tab[i][0] == '\'' && tab[i][len - 1] == '\'') {
        tmp = strndup(&tab[i][1], len - 2);
        free(tab[i]);
        tab[i] = tmp;
    }
}

int correct_tab(char **tab)
{
    for (int i = 0; tab[i] != NULL; i++) {
        if (check_element(tab, i) == FALSE) {
            free_array(tab);
            return FALSE;
        }
    }
    return TRUE;
}
