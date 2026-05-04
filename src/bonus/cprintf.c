/*
** EPITECH PROJECT, 2026
** cprintf
** File description:
** color printf
*/

#include "../../include/struct.h"

int cprintf(char *str, char *color)
{
    write(1, color, strlen(color));
    write(1, str, strlen(str));
    write(1, NORMAL, strlen(NORMAL));
    return SUCCESS_EXIT;
}
