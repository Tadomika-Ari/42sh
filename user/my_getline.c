/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** my_getline
*/

#include "../include/struct.h"
#include <termios.h>

int my_getline(char **cmd, size_t *len)
{
    return getline(cmd, len, stdin);
}
