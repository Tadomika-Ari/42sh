/*
** EPITECH PROJECT, 2026
** put
** File description:
** err
*/

#include "../../include/struct.h"

int put_err(char *str)
{
    write(1, str, my_strlen(str));
    return FALSE;
}
