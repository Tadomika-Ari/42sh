/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** len_array
*/

#include "my.h"

int len_array(char **array)
{
    int i = 0;

    if (!array)
        return 0;
    for (; array[i] != 0; i++);
    return i;
}
