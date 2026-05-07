/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** cut_len
*/

#include "../../include/struct.h"

char *cut_len(char *str, int nbr)
{
    int nbmalloc = my_strlen(str) - nbr;
    char *change = NULL;
    int y = 0;

    if (nbmalloc <= 0)
        return NULL;
    change = malloc(nbmalloc + 1);
    if (change == NULL)
        return NULL;
    for (int i = nbr; str[i] != '\0'; i++) {
        change[y] = str[i];
        y++;
    }
    change[y] = '\0';
    return change;
}
