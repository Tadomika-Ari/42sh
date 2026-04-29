/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if
*/

#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "../../include/struct.h"

static int fallback_cond(char *expr)
{
    int left = 0;
    int right = 0;

    if (expr && sscanf(expr, " ( %d == %d ) ", &left, &right) == 2)
        return left == right;
    if (expr && sscanf(expr, "(%d==%d)", &left, &right) == 2)
        return left == right;
    return 0;
}

static char *join_expr(char **argv)
{
    size_t len = 0;
    size_t pos = 0;
    char *expr = NULL;

    if (argv == NULL)
        return NULL;
    for (int i = 0; argv[i] != NULL && my_strcmp(argv[i], "then") != 0; i++)
        len += strlen(argv[i]) + 1;
    expr = malloc(len + 1);
    if (expr == NULL)
        return NULL;
    for (int i = 0; argv[i] != NULL && my_strcmp(argv[i], "then") != 0; i++) {
        memcpy(expr + pos, argv[i], strlen(argv[i]));
        pos += strlen(argv[i]);
        if (argv[i + 1] != NULL && my_strcmp(argv[i + 1], "then") != 0) {
            expr[pos] = ' ';
            pos++;
        }
    }
    expr[pos] = '\0';
    return expr;
}

static int search_condition(tcsh_t *term, char **argv, bool *error)
{
    char *expr = join_expr(argv);
    int cond = 0;

    (void)term;
    if (expr == NULL) {
        *error = true;
        return ALTERNATIVE_EXIT;
    }
    cond = fallback_cond(expr);
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

int else_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if ((cond != 0 && then == 1))
        return SUCCESS_EXIT;
    if (cond != 0 && then == 0) {
        search_command(term, argv + 1, NULL);
        return SUCCESS_EXIT;
    }
    return ALTERNATIVE_EXIT;
}

static char **get_info(void)
{
    size_t len = 0;
    char *lign = NULL;
    char **tmp = NULL;

    if (getline(&lign, &len, stdin) == -1) {
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

    while (1) {
        tmp = get_info();
        if (stop(tmp) == 0) {
            free_array(tmp);
            return SUCCESS_EXIT;
        }
        if (strcmp(tmp[0], "else") == 0 && else_if(term, tmp + 2) == 0) {
            free_array(tmp);
            return SUCCESS_EXIT;
        }
        free_array(tmp);
    }
}

int my_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = is_then(argv);

    if (cond == 0)
        cond = fallback_cond(argv[0]);
    if (error == true || then == -1)
        return ALTERNATIVE_EXIT;
    if (cond != 0 && then == 0 && argv[1] != NULL)
        return search_command(term, argv + 1, NULL);
    if ((cond != 0 && then == 1) || (cond == 0 && then == 0))
        return SUCCESS_EXIT;
    return in_if(term);
}
