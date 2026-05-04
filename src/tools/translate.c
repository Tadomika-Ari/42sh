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
    if (search_variable(term, str) == 1)
        return NULL;
    if (is_globing(str->data) == TRUE)
        return globbing(str->data);
    if (((char *)str->data)[0] == '\0') {
        res = array_null('\0');
        return res;
    }
    res = parser3000(str->data, " ");
    check_quote(res);
    return res;
}
