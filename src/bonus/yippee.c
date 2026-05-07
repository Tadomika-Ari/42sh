/*
** EPITECH PROJECT, 2026
** mambo
** File description:
** mambo
*/

#include "../../include/struct.h"

int yippee(tcsh_t *term, char **argv)
{
    play_sound(YIPPEE_SONG);
    return SUCCESS_EXIT;
}
