/*
** EPITECH PROJECT, 2025
** cat str
** File description:
** cat
*/

#include "my.h"

char *my_strcat(char *dest, char *src)
{
    int comp = my_strlen(dest);

    for (int i = 0; i != my_strlen(src) + 1; i++){
        dest[comp + i] = src[i];
    }
    return (dest);
}
