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

char *simple(char c)
{
    char *str = malloc(sizeof(char) * 2);

    if (!str)
        return NULL;
    str[0] = c;
    str[1] = '\0';
    return str;
}

char **array_null(char c)
{
    char **array = malloc(sizeof(char *) * (2));
    char *str = NULL;

    if (!array)
        return NULL;
    str = simple(c);
    if (str == NULL) {
        free(array);
        return NULL;
    }
    array[0] = str;
    array[1] = NULL;
    return array;
}

static void variable(tcsh_t *term, nodes_t *str)
{
    for (nodes_t *tmp = term->locals; tmp && str; tmp = tmp->next)
        if (((char *)str->data)[0] == '$' && my_strcmp(str->data + 1,
                ((locals_t *)tmp->data)->name) == 0) {
            free(str->data);
            str->data = ((locals_t *)tmp->data)->value != NULL ?
                strdup(((locals_t *)tmp->data)->value) : my_strdup("\0");
        }
    if (str && my_strcmp(str->data, "$?") == 0){
        free(str->data);
        str->data = simple(term->return_value + 48);
    }
}

char *strip_quotes(char *word)
{
    int len = 0;
    int j = 0;
    char *result = NULL;

    if (word == NULL)
        return NULL;
    len = my_strlen(word);
    result = malloc(sizeof(char) * (len + 1));
    if (result == NULL)
        return NULL;
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] != '\'' && word[i] != '"') {
            result[j] = word[i];
            j++;
        }
    }
    result[j] = '\0';
    return result;
}

static void check_quote(char **tab)
{
    char *tmp = NULL;

    for (int i = 0; tab[i] != NULL; i++) {
        tmp = tab[i];
        tab[i] = strip_quotes(tmp);
        free(tmp);
    }
}

char **translate(tcsh_t *term, nodes_t *str)
{
    char **res = NULL;

    if (is_inihbitor(str->data) == TRUE)
        return solo_tab(str->data);
    variable(term, str);
    if (((char *)str->data)[0] == '\0') {
        res = array_null('\0');
        return res;
    }
    res = parser3000(str->data, " ");
    variable(term, str);
    check_quote(res);
    return res;
}
