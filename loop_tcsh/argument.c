/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** argument
*/

#include "../include/struct.h"

static int take_argument(char **cmd, tcsh_t *term)
{
    size_t len = 0;

    if (getline(cmd, &len, stdin) == -1) {
        if (isatty(0) == 0)
            return FAILURE_EXIT;
        write(1, "exit\n", 5);
        term->life = DEAD;
        return SUCCESS_EXIT;
    }
    if (!*cmd)
        return FAILURE_EXIT;
    push_to_history(term, cmd[0]);
    return SUCCESS_EXIT;
}

char *take_value(nodes_t *head, char *cat)
{
    char *res = NULL;
    nodes_t *tmp = search_node(head, cat);

    if (!tmp)
        return NULL;
    res = tmp->data;
    return res + my_strn(res, "=");
}

void write_argument(char **cmd, tcsh_t *term)
{
    char *lign = take_value(term->env, "HOST");
    char *user = take_value(term->env, "USERNAME");
    int tmp = 0;

    if (lign)
        write(1, lign, strlen(lign));
    write(1, ":", 1);
    lign = take_value(term->env, "PWD");
    if (lign && user) {
        tmp = my_strn(lign, user);
        if (tmp != 0)
            write(1, "~", 1);
        write(1, lign + tmp, strlen(lign + tmp));
    }
    write(1, "> ", 2);
}

int user_entry(tcsh_t *term, char **cmd)
{
    if (isatty(0) != 0)
        write_argument(cmd, term);
    return take_argument(cmd, term);
}
