/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** all_for_len
*/

#include "../../include/struct.h"

int all_for_len(tcsh_t *term, history_t *tmp)
{
    int len = my_strlen(tmp->cmd);

    if (len > 0 && tmp->cmd[len - 1] == '\n')
        len--;
    term->maxposcursor = len;
    term->whereiscursor = len;
    return len;
}
