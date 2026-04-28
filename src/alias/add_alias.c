/*
** EPITECH PROJECT, 2026
** add_alias.c
** File description:
** add_alias
*/

#include "../../include/struct.h"

static int check_tab(char **tab, char *buf_rc)
{
    if (tab == NULL)
        return FAILURE_EXIT;
    if (tab[0] == NULL) {
        free_array(tab);
        free(buf_rc);
        return SUCCESS_EXIT;
    }
    return 42;
}

int print_alias(tcsh_t *term)
{
    char *buf_rc = get_rc_file(term);
    char **tab = NULL;
    char *tmp = NULL;
    int value = 0;

    if (buf_rc == NULL)
        return SUCCESS_EXIT;
    tab = parser3000(buf_rc, " \n=");
    value = check_tab(tab, buf_rc);
    if (value != 42)
        return value;
    for (int i = 0; i <= len_array(tab) - 3; i += 3) {
        tmp = strip_single_quotes(tab[i + 2]);
        printf("%s (%s)\n", tab[i + 1], tmp);
        free(tmp);
    }
    free_array(tab);
    free(buf_rc);
    return SUCCESS_EXIT;
}

int my_alias(tcsh_t *term, char **cmd)
{
    if (cmd[0] == NULL)
        return print_alias(term);
    if (cmd[1] == NULL)
        return SUCCESS_EXIT;
    if (my_strcmp("alias", cmd[0]) == 0) {
        put_err("alias: Too dangerous to alias that.\n");
        return ALTERNATIVE_EXIT;
    }
    if (my_strcmp(cmd[0], cmd[1]) == 0)
        return SUCCESS_EXIT;
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
