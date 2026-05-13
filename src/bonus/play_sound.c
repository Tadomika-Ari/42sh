/*
** EPITECH PROJECT, 2026
** play
** File description:
** sound
*/

#include "../../include/struct.h"

int play_sound(char *filename)
{
    char command[MAX_LINE];

    if (!filename)
        return FAILURE_EXIT;
    snprintf(command, sizeof(command), SOUND_STRUCT, filename);
    system(command);
    return SUCCESS_EXIT;
}
