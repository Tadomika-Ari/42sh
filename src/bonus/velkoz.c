/*
** EPITECH PROJECT, 2026
** velkoz
** File description:
** velkoz
*/

#include "../../include/struct.h"

int my_velkoz(tcsh_t *term, char **cmd)
{
    char *buff = NULL;
    int len = len_array(cmd);

    buff = fill_buff_bonus(VELKOZ);
    if (!buff)
        return FAILURE_EXIT;
    printf("\033[35m%s\033[0m\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}