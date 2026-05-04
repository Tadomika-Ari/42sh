/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** len_base
*/

#include "../../include/struct.h"

int my_lenbase(int nb, int base)
{
    int len = 0;

    if (nb < 0) {
        nb = nb * -1;
        len++;
    }
    while (base <= nb) {
        nb = nb / base;
        len++;
    }
    len++;
    return len;
}
