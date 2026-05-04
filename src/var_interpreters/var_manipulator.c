/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** var_interpreter
*/

#include "../../include/struct.h"

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

char *my_str_rea(char *base, char *value)
{
    int len = my_strlen(base);
    int i = len;

    if (!value)
        return base;
    base = realloc(base, sizeof(char) * (len + my_strlen(value) + 1));
    if (!base)
        return NULL;
    for (int d = 0; value[d]; d++) {
        base[i] = value[d];
        i++;
    }
    base[i] = '\0';
    return base;
}

char *without(char *str)
{
    char *res = malloc(sizeof(char) * (my_strlen(str)));
    int j = 0;

    if (!res)
        return str;
    for (int i = 0; str[i]; i++) {
        if (str[i] == '{' || str[i] == '}')
            continue;
        res[j] = str[i];
        j++;
    }
    res[j] = '\0';
    return res;
}

char *get_name(char *str, int max)
{
    char *res = malloc(sizeof(char) * (max + 2));

    if (!res)
        return NULL;
    for (int i = 0; i != max + 1; i++) {
        res[i] = str[i];
    }
    res[max + 1] = '\0';
    return res;
}
