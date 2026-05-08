/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** else
*/

#include "../../include/struct.h"

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

int search_condition(tcsh_t *term, char **argv, bool *error)
{
    char *expr = join(argv);
    int cond = 0;

    if (expr == NULL || expr[0] == '\0') {
        *error = true;
        if (expr)
            free(expr);
        return ALT_EXIT;
    }
    cond = fallback_cond(term, expr, error);
    if (*error == true) {
        free(expr);
        return ALT_EXIT;
    }
    if (cond == 0 && atoi(expr) != 0)
        cond = 1;
    free(expr);
    return cond;
}

int exec_if(char **lign, char **action, tcsh_t *term, int *cond)
{
    bool error = false;
    int res = -2;
    int then = is_then(lign);

    if (search_variable(term, (nodes_t *)(&lign[1])) == ALT_EXIT)
        return ALT_EXIT;
    *cond = search_condition(term, lign + 1, &error);
    if (error == true)
        res = my_cmd_error(": Too few arguments.\n", "if", ALT_EXIT);
    if (lign[1] == NULL)
        res = my_cmd_error(": Empty if.\n", "if", ALT_EXIT);
    if (*cond == 0 && res != ALT_EXIT)
        res = SUCCESS_EXIT;
    if (*cond != 0 && lign[1] != NULL && res != ALT_EXIT && then == 0)
        res = apply(term, dupl_array(lign + 2));
    if (*cond != 0 && res != ALT_EXIT && then == 1)
        res = execute_cmd(term, action + 1);
    return res;
}

int exec_else(char **lign, char **action, tcsh_t *term, int *cond)
{
    int res = -2;

    if (len_array(lign) == 1 && *cond == 0)
        res = execute_cmd(term, action + 1);
    if (lign[1] != NULL && my_strcmp(lign[1], "if") == 0 &&
        *cond == 0 && res == -2)
        res = exec_if(lign + 1, action, term, cond);
    if (res == -2)
        res = SUCCESS_EXIT;
    free_array(lign);
    return res;
}
