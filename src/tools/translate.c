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

char **array_null(void)
{
    char **array = malloc(sizeof(char *) * (2));

    if (!array)
        return NULL;
    array[0] = my_strdup("\0");
    array[1] = NULL;
    return array;
}

char **translate(tcsh_t *term, nodes_t *str)
{
    char **res = NULL;

    if (is_inihbitor(str->data) == TRUE)
        return solo_tab(str->data);
    for (nodes_t *tmp = term->locals; tmp && str; tmp = tmp->next)
        if (((char *)str->data)[0] == '$' && my_strcmp(str->data + 1,
                ((locals_t *)tmp->data)->name) == 0) {
            free(str->data);
            str->data = ((locals_t *)tmp->data)->value != NULL ?
                strdup(((locals_t *)tmp->data)->value) : my_strdup("\0");
        }
    if (((char *)str->data)[0] == '\0') {
        res = array_null();
        return res;
    }
    res = my_str_to_word_array(str->data, " ");
    return res;
}
