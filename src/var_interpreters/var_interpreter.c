/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** var_interpreter
*/

#include "../../include/struct.h"

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
        res = my_str_rea(res, tmp[i]);
        res = my_str_rea(res, value);
    }
    res = my_str_rea(res, tmp[i]);
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
        if (!value)
            str->data = my_strdup("");
        else
            str->data = my_strdup(value);
        free(name);
        return SUCCESS_EXIT;
    }
    tmp = my_strtwabw(str->data, name);
    if (!value)
        return replace_in_str(str, "", name, tmp);
    return replace_in_str(str, value, name, tmp);
}

static int special(nodes_t *str, char *var, char *name)
{
    char *pwd = NULL;
    int res = 0;

    pwd = getcwd(pwd, 0);
    res = replace(str, pwd, var, name);
    if (pwd)
        free(pwd);
    return res;
}

static int search_var(tcsh_t *term, nodes_t *str, char *var, char *name)
{
    char *value = NULL;

    if (!var || !name)
        return ALTERNATIVE_EXIT;
    for (nodes_t *tmp = term->locals; tmp; tmp = tmp->next)
        if (my_strcmp(((locals_t *)tmp->data)->name, name + 1) == 0)
            return replace(str, ((locals_t *)tmp->data)->value, var, name);
    value = take_value(term->env, name + 1);
    if (value)
        return replace(str, value, var, name);
    if (var[1] == '?' && var[2] == '\0')
        return replace(str, term->return_value, var, name);
    if (my_strcmp(name, "$cwd") == 0)
        return special(str, var, name);
    my_cmd_error(": Undefined variable.\n", name + 1, ALTERNATIVE_EXIT);
    free(var);
    return ALTERNATIVE_EXIT;
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

static int check(tcsh_t *term, nodes_t *str, int i)
{
    return (interpreter(term, str, i) != SUCCESS_EXIT ? -1 : 0);
}

int search_variable(tcsh_t *term, nodes_t *str)
{
    int i = 0;

    while (((char *)str->data)[i]) {
        i = ((char *)str->data)[i] == '$' ? check(term, str, i) : i + 1;
        if (i == 0)
            continue;
        if (i == -1)
            return ALTERNATIVE_EXIT;
    }
    return SUCCESS_EXIT;
}
