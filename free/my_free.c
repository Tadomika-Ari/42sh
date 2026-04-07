/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** my_free
*/

#include "../include/struct.h"

int my_free(void **pointer, int max, int exit)
{
    for (int i = 0; i < max; i++) {
        if (pointer[i]) {
            free(pointer[i]);
            pointer[i] = NULL;
        }
    }
    return exit;
}
