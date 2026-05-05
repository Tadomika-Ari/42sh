/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if
*/

#include "../../include/struct.h"

static int apply(tcsh_t *term, char **cmd)
{
    int status = 0;

    if (!cmd || cmd[0] == NULL)
        return ALTERNATIVE_EXIT;
    for (nodes_t *tmp = term->func; tmp; tmp = tmp->next)
        if (my_strcmp(cmd[0], ((function_t *)tmp->data)->name) == 0)
            return execute(tmp, cmd, term);
    status = search_command(term, cmd, NULL);
    return normalize(term, NULL, cmd, status);
}

static char *join(char **argv)
{
    int pos = 0;
    int len = join_len_until_then(argv);
    char *res = NULL;

    if (argv == NULL)
        return NULL;
    res = malloc(len + 1);
    if (res == NULL)
        return NULL;
    for (int i = 0; argv[i] != NULL && not_cond(argv[i]) == 0; i++) {
        memcpy(res + pos, argv[i], strlen(argv[i]));
        pos += strlen(argv[i]);
        if (argv[i + 1] != NULL && my_strcmp(argv[i + 1], "then") != 0) {
            res[pos] = ' ';
            pos++;
        }
    }
    res[pos] = '\0';
    return res;
}

static int search_condition(tcsh_t *term, char **argv, bool *error)
{
    char *expr = join(argv);
    int cond = 0;

    if (expr == NULL || expr[0] == '\0') {
        *error = true;
        if (expr)
            free(expr);
        return ALTERNATIVE_EXIT;
    }
    cond = fallback_cond(term, expr, error);
    if (*error == true) {
        free(expr);
        return ALTERNATIVE_EXIT;
    }
    if (cond == 0 && atoi(expr) != 0)
        cond = 1;
    free(expr);
    return cond;
}

static int is_then(char **argv)
{
    int res = 0;

    if (argv == NULL)
        return res;
    for (int i = 0; argv[i]; i++) {
        if (my_strcmp(argv[i], "then") == 0 && argv[i + 1] == NULL) {
            res = 1;
            return res;
        }
        if (my_strcmp(argv[i], "then") == 0 && argv[i + 1] != NULL) {
            res = -1;
            return res;
        }
    }
    return res;
}

static int stop(char **argv)
{
    if (argv == NULL || argv[0] == NULL)
        return ALTERNATIVE_EXIT;
    if (my_strcmp("else", argv[0]) == 0) {
        if (argv[1] == NULL)
            return SUCCESS_EXIT;
        return ALTERNATIVE_EXIT;
    }
    if (my_strcmp("endif", argv[0]) == 0)
        return SUCCESS_EXIT;
    return ALTERNATIVE_EXIT;
}

char **dupl_array(char **argv)
{
    int len = len_array(argv);
    char **array = malloc(sizeof(char *) * (len + 1));

    if (!array)
        return NULL;
    for (int i = 0; argv[i]; i++) {
        array[i] = my_strdup(argv[i]);
        if (array[i] == NULL)
            return array;
    }
    array[len] = NULL;
    return array;
}

int else_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if ((cond != 0 && then == 1))
        return SUCCESS_EXIT;
    if (cond != 0 && then == 0)
        return apply(term, dupl_array(argv + 1));
    return ALTERNATIVE_EXIT;
}

static char **get_info(bool *stop)
{
    size_t len = 0;
    char *lign = NULL;
    char **tmp = NULL;

    if (getline(&lign, &len, stdin) == -1) {
        *stop = true;
        free(lign);
        return NULL;
    }
    tmp = parser3000(lign, " \t\n");
    if (tmp == NULL || tmp[0] == NULL) {
        free_array(tmp);
        free(lign);
        return NULL;
    }
    free(lign);
    return tmp;
}

int in_if(tcsh_t *term)
{
    char **tmp = NULL;
    int res = -1;
    bool cond = false;

    while (1) {
        tmp = get_info(&cond);
        if (cond == true)
            return my_cmd_error(": then/endif not found.\n",
                "then", ALTERNATIVE_EXIT);
        if (stop(tmp) == 0) {
            free_array(tmp);
            return SUCCESS_EXIT;
        }
        res = strcmp(tmp[0], "else") == 0 ? else_if(term, tmp + 2) : res;
        if (res != ALTERNATIVE_EXIT) {
            free_array(tmp);
            return res;
        }
        free_array(tmp);
    }
}

int my_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (error == true || then == -1)
        return my_cmd_error(": Too few arguments.\n", "if", ALTERNATIVE_EXIT);
    if (then == 0) {
        if (cond != 0 && argv[1] != NULL)
            return apply(term, dupl_array(argv + 1));
        if (argv[1] == NULL)
            return my_cmd_error(": Empty if.\n", "if", ALTERNATIVE_EXIT);
        return SUCCESS_EXIT;
    }
    if (cond != 0 && then == 1)
        return SUCCESS_EXIT;
    return in_if(term);
}
