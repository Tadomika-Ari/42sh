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

static char *get_name(char *str, int max)
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

static char *get_variable(char *str)
{
    bool parenthesis = false;
    char *res = NULL;

    for (int i = 1; str[i]; i++) {
        if (str[i] == '{' && i == 1)
            parenthesis = true;
        if (str[i] == '}' && parenthesis == true) {
            res = get_name(str, i);
            break;
        }
        if (((str[i] < 'A' || str[i] > 'Z') && (str[i] < 'a' || str[i] > 'z') &&
                (str[i] < '0' || str[i] > '9') && parenthesis == false)
            || str[i + 1] == '\0') {
            res = get_name(str, i);
            break;
        }
    }
    return res;
}

char *my_strncat(char *base, char *value)
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

static int replace_in_str(nodes_t *str, char *value, char *name, char **tmp)
{
    char *res = NULL;
    int i = 0;

    if (!tmp) {
        free(name);
        return ALTERNATIVE_EXIT;
    }
    free(name);
    for (; tmp[i + 1] != NULL; i++) {
        res = my_strncat(res, tmp[i]);
        res = my_strncat(res, value);
    }
    res = my_strncat(res, tmp[i]);
    free_array(tmp);
    if (!res)
        return ALTERNATIVE_EXIT;
    if (str->data)
        free(str->data);
    str->data = res;
    return SUCCESS_EXIT;
}

static int replace(nodes_t *str, char *value, char *name, char *named)
{
    char **tmp = NULL;

    if (named && named != name)
        free(named);
    if (my_strcmp(str->data, name) == 0) {
        free(str->data);
        str->data = my_strdup(value);
        free(name);
        return SUCCESS_EXIT;
    }
    tmp = my_strtwabw(str->data, name);
    return replace_in_str(str, value, name, tmp);
}

static int search_var(tcsh_t *term, nodes_t *str, char *var, char *name)
{
    char *value = NULL;

    if (!var || !name)
        return ALTERNATIVE_EXIT;
    for (nodes_t *tmp = term->locals; tmp; tmp = tmp->next) {
        if (my_strcmp(((locals_t *)tmp->data)->name, name + 1) == 0)
            return replace(str, ((locals_t *)tmp->data)->value, var, name);
    }
    value = take_value(term->env, name + 1);
    if (value)
        return replace(str, value, var, name);
    if (var[1] == '?' && var[2] == '\0')
        return replace(str, term->return_value, var, name);
    my_cmd_error(": Undefined variable.\n", name + 1);
    free(var);
    return ALTERNATIVE_EXIT;
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

static int interpreter(tcsh_t *term, nodes_t *str, int i)
{
    char *name = NULL;

    if (((char *)str->data)[i] == '$') {
        name = get_variable(&((char *)str->data)[i]);
        if (name && name[1] == '{')
            return search_var(term, str, name, without(name));
        return search_var(term, str, name, name);
    }
    return SUCCESS_EXIT;
}

int search_variable(tcsh_t *term, nodes_t *str)
{
    int i = 0;

    while (((char *)str->data)[i]) {
        if (((char *)str->data)[i] == '$') {
            if (interpreter(term, str, i) != SUCCESS_EXIT)
                return ALTERNATIVE_EXIT;
            i = 0;
            continue;
        }
        i++;
    }
    return SUCCESS_EXIT;
}
