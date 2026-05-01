/*
** EPITECH PROJECT, 2026
** fill
** File description:
** bonus
*/

#include "../../include/struct.h"

int pelophylax(tcsh_t *term, char **argv)
{
    printf("PELOPHYLAX KL ESCULENTUS\n");
    return SUCCESS_EXIT;
}

int fill_bonus(tcsh_t *term)
{
    if (push_function(term, pelophylax "pelophylax") == FAILURE_EXIT)
        return FAILURE_EXIT;
    return EXIT_SUCCESS;
}
