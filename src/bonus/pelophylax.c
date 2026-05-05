/*
** EPITECH PROJECT, 2026
** pelophylax
** File description:
** pelophylax
*/

#include "../../include/struct.h"

int pelophylax(tcsh_t *term, char **argv)
{
    char *buff = fill_buff_bonus(PELOPHYLAX);

    if (!buff)
        return FAILURE_EXIT;
    printf("\033[32m%s\033[0m\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}
