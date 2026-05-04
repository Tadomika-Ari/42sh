/*
** EPITECH PROJECT, 2026
** bouns
** File description:
** bonus
*/

#include "../../include/struct.h"

int flipcoin(tcsh_t *term, char **argv)
{
    int odds = rand() % 2;

    if (odds == 0)
        printf("Tail\n");
    else
        printf("Head\n");
    return SUCCESS_EXIT;
}
