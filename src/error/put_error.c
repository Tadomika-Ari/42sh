/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_message
*/

#include "../../include/struct.h"

int put_err(char *str, int flags)
{
    write(2, str, my_strlen(str));
    return flags;
}
