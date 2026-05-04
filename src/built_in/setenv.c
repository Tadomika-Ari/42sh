/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** setenv
*/

#include "../../include/struct.h"

char *new_categorize(char *categorize)
{
    char *res = malloc(sizeof(char) * (my_strlen(categorize) + 2));

    if (!res)
        return NULL;
    res[0] = 0;
    my_strcat(res, categorize);
    my_strcat(res, "=");
    return res;
}

char *new_line(char *categorize, char *value)
{
    char *res = malloc(sizeof(char) *
        (my_strlen(categorize) + my_strlen(value) + 2));

    if (!res)
        return NULL;
    res[0] = 0;
    my_strcat(res, categorize);
    my_strcat(res, "=");
    my_strcat(res, value);
    return res;
}

int replace_lign(tcsh_t *term, char *lign, char *categorize)
{
    nodes_t *tmp = NULL;

    for (tmp = term->env; tmp; tmp = tmp->next) {
        if (!tmp->data)
            continue;
        if (my_strcmp(tmp->data, categorize) == 0) {
            free(tmp->data);
            tmp->data = lign;
            return SUCCESS_EXIT;
        }
    }
    tmp = create_new_node(my_strdup(lign));
    free(lign);
    push_back(&term->env, tmp);
    return SUCCESS_EXIT;
}

int correct_name(char *name, char *cmd)
{
    if ((name[0] < 'a' || name[0] > 'z') &&
        (name[0] < 'A' || name[0] > 'Z') && name[0] != '_')
        return error_first_caracter(cmd);
    if (my_str_name(name) != 0)
        return error_alphanumeric(cmd);
    return SUCCESS_EXIT;
}

int my_setenv(tcsh_t *term, char **argv)
{
    char *lign = NULL;
    int len = len_array(argv);

    if (len > 2)
        return error_too_many_argument("setenv");
    if (len == 0)
        return env(term, NULL);
    if (correct_name(argv[0], "setenv") == ALTERNATIVE_EXIT)
        return ALTERNATIVE_EXIT;
    if (len == 1)
        lign = new_categorize(argv[0]);
    else
        lign = new_line(argv[0], argv[1]);
    if (!lign)
        return FAILURE_EXIT;
    return replace_lign(term, lign, argv[0]);
}
