/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** if
*/

#include "../../include/struct.h"

int apply(tcsh_t *term, char **cmd)
{
    int status = 0;

    if (!cmd || cmd[0] == NULL)
        return ALT_EXIT;
    for (nodes_t *tmp = term->func; tmp; tmp = tmp->next)
        if (my_strcmp(cmd[0], ((function_t *)tmp->data)->name) == 0)
            return execute(tmp, cmd, term);
    status = search_command(term, cmd, NULL);
    return normalize(term, NULL, cmd, status);
}

int is_then(char **argv)
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

static int begin_with(char *argv)
{
    bool cond = false;
    char **tmp = my_str_to_word_array(argv, " \t\n");

    if (tmp == NULL)
        return ALT_EXIT;
    if (my_strcmp(tmp[0], "else") == 0)
        cond = true;
    if (cond == false && my_strcmp(tmp[0], "if") == 0)
        cond = true;
    free_array(tmp);
    return cond;
}

int execute_cmd(tcsh_t *term, char **argv)
{
    int res = 0;

    if (!argv)
        return ALT_EXIT;
    for (int i = 0; argv[i] && begin_with(argv[i]) == 0; i++) {
        res = from_one_line(term, my_strdup(argv[i]));
        if (res != SUCCESS_EXIT)
            return ALT_EXIT;
    }
    return res;
}

static int choice_good(char **action, tcsh_t *term, char *verif, int *cond)
{
    char **tmp = parser3000(verif, " \t\n");

    if (tmp == NULL)
        return SUCCESS_EXIT;
    if (my_strcmp(tmp[0], "if") == 0)
        return exec_if(tmp, action, term, cond);
    if (my_strcmp(tmp[0], "else") == 0)
        return exec_else(tmp, action, term, cond);
    free_array(tmp);
    return SUCCESS_EXIT;
}

static int in_if(tcsh_t *term, int cond)
{
    bool error = false;
    char **tmp = take_action(&error, "endif");
    int res = 0;

    if (error == true)
        return my_cmd_error(": then/endif not found.\n", "then", ALT_EXIT);
    if (cond != 0)
        res = execute_cmd(term, tmp);
    for (int i = 0; tmp[i] != NULL && res != ALT_EXIT; i++) {
        res = choice_good(&tmp[i], term, tmp[i], &cond);
        if (res == ALT_EXIT)
            break;
    }
    free_array(tmp);
    return res;
}

int my_if(tcsh_t *term, char **argv)
{
    bool error = false;
    int cond = search_condition(term, argv, &error);
    int then = 0;

    if (error == true && len_array(argv) > 0)
        return ALT_EXIT;
    then = is_then(argv);
    if (error == true || then == -1)
        return my_cmd_error(": Too few arguments.\n", "if", ALT_EXIT);
    if (then == 0) {
        if (cond != 0 && argv[1] != NULL)
            return apply(term, dupl_array(argv + 1));
        if (argv[1] == NULL)
            return my_cmd_error(": Empty if.\n", "if", ALT_EXIT);
        return SUCCESS_EXIT;
    }
    return in_if(term, cond);
}
