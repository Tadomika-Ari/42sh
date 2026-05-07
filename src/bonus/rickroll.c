/*
** EPITECH PROJECT, 2026
** rickroll
** File description:
** rickroll
*/

#include "../../include/struct.h"

int rickroll(void)
{
    int odd = rand() % 100;
    char *buff = NULL;

    if (odd <= RICKROLL_ODDS) {
        buff = fill_buff_bonus(RICKROLL_TXT);
        if (!buff)
            return FAILURE_EXIT;
        printf("\033[32m%s\033[0m\n", buff);
        free(buff);
        play_sound(RICKROLL);
        return SUCCESS_EXIT;
    }
    return SUCCESS_EXIT;
}
