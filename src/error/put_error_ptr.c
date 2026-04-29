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
