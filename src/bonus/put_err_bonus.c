/*
** EPITECH PROJECT, 2026
** put
** File description:
** err
*/

#include "../../include/struct.h"

int put_err(char *str, int flags)
{
    cprintf(str, RED);
    rickroll();
    return flags;
}
