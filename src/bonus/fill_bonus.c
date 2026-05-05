/*
** EPITECH PROJECT, 2026
** fill
** File description:
** bonus
*/

#include "../../include/struct.h"

int fill_bonus(tcsh_t *term)
{
    if (push_function(term, pelophylax, "pelophylax") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, tic_tac_toe, "tic_tac_toe") == FAILURE_EXIT)
        return FAILURE_EXIT;
    return EXIT_SUCCESS;
}
