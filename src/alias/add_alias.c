/*
** EPITECH PROJECT, 2026
** add_alias.c
** File description:
** add_alias
*/

#include "../../include/struct.h"

int my_alias(tcsh_t *term, char **cmd)
{
    if (cmd[0] == NULL || cmd[1] == NULL)
        return ALTERNATIVE_EXIT;
    if (my_strcmp("alias", cmd[0]) == 0) {
        put_err("alias: Too dangerous to alias that.\n");
        return ALTERNATIVE_EXIT;
    }
    write(term->fd_rc, "alias ", 6);
    for (int i = 0; cmd[i] != NULL; i++) {
        write(term->fd_rc, cmd[i], my_strlen(cmd[i]));
        if (i > 0 && cmd[i + 1] != NULL)
            write(term->fd_rc, " ", 1);
        if (i < 1)
            write(term->fd_rc, "=\'", 2);
    }
    write(term->fd_rc, "\'\n", 2);
    return SUCCESS_EXIT;
}
