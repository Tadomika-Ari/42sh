/*
** EPITECH PROJECT, 2026
** correct
** File description:
** tab
*/

#include "../../include/struct.h"

static int occ_in_str(char c, char *str)
{
    int occ = 0;

    for (int i = 0; str[i] != '\0'; i++) {
        if (c == str[i])
            occ++;
    }
    return occ;
}

static void update_element(char **str)
{
    int len = my_strlen(*str);
    char *res = malloc(sizeof(char) * (len - 1));
    int j = 0;

    if (!res)
        return;
    for (int i = 0; (*str)[i] != '\0'; i++) {
        if ((*str)[i] != '\'') {
            res[j] = (*str)[i];
            j++;
        }
    }
    res[j] = '\0';
    free(*str);
    *str = res;
}

int unmatch_single(char **str)
{
    int occ = occ_in_str('\'', *str);

    if (occ == 1)
        return TRUE;
    if (occ != 2)
        return FALSE;
    update_element(str);
    return FALSE;
}

int check_element(char **tab, int i)
{
    if (unmatch_single(&tab[i]) == TRUE)
        return put_err(UNMATCH_SINGLE);
    return TRUE;
}

void change(char **tab, int i)
{
    int len = my_strlen(tab[i]);
    char *tmp = NULL;

    if (tab[i][0] == '\'' && tab[i][len - 1] == '\'') {
        tmp = strndup(tab[i] + 1, len - 2);
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
        if (my_strlen(tab[i]) > 1) {
            change(tab, i);
        }
    }
    return TRUE;
}
