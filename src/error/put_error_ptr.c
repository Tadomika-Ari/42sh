/*
** EPITECH PROJECT, 2026
** my_puterror
** File description:
** my_puterror
*/

#include "../../include/struct.h"

void *my_puterror_ptr(char *message)
{
    write(2, message, my_strlen(message));
    return NULL;
}

int my_cmd_error(char *str, char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, str, my_strlen(str));
    return ALTERNATIVE_EXIT;
}
