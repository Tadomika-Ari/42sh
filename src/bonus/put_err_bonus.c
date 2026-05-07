/*
** EPITECH PROJECT, 2026
** put
** File description:
** err
*/

#include "../../include/struct.h"

int put_err(char *str, int flags)
{
    int odd = rand() % 100;

    cprintf(str, RED);
    if (odd <= RICKROLL_ODDS)
        play_sound(RICKROLL);
    return flags;
}
