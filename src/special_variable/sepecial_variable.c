/*
** EPITECH PROJECT, 2026
** special_variable
** File description:
** my_cwd
*/

#include "../../include/struct.h"

int sepecial_variable(tcsh_t *term, char *cmd)
{
    char *path = NULL;

    if (cmd[0] != '$')
        return -1;
    my_strupcase(cmd);
    if (my_strcmp("$CWD", cmd) == 0)
        path = take_value(term->env, "PWD");
    else
        path = take_value(term->env, cmd + 1);
    if (path == NULL)
        return -1;
    write(1, path, my_strlen(path));
    write(1, "\n", 1);
    return SUCCESS_EXIT;
}
