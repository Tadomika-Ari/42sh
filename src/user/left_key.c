/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** left_key
*/

#include "../../include/struct.h"

int left_key(tcsh_t *term, getline_t *st_g)
{
    write(STDOUT_FILENO, "\x1b[D", 3);
    return 0;
}
