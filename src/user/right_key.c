/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** right_key
*/

#include "../../include/struct.h"

int right_key(tcsh_t *term, getline_t *st_g)
{
    write(STDOUT_FILENO, "\x1b[C", 3);
    return 0;
}
