/*
** EPITECH PROJECT, 2026
** tic_tac_toe
** File description:
** tic_tac_toe
*/

#include "../../include/struct.h"

int help(void)
{
    char *buf = fill_buff("bonus/tic_tac_toe.txt");

    cprintf(buf, BLUE);
    return SUCCESS_EXIT;
}

int tic_tac_toe(tcsh_t *term, char **argv)
{
    if (my_strcmp(argv[0], "-h") == 0)
        return help();
    return SUCCESS_EXIT;
}
