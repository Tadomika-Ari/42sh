/*
** EPITECH PROJECT, 2026
** fill
** File description:
** bonus
*/

#include "../../include/struct.h"

int fill_bonus(tcsh_t *term)
{
    srand(time(NULL));
    if (push_function(term, pelophylax, "pelophylax") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, tic_tac_toe, "tictactoe") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, hangman, "hangman") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, flipcoin, "flipcoin") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, throwdice, "throwdice") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, guessnumber, "guessnumber") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, author, "author") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, mambo, "mambo") == FAILURE_EXIT)
        return FAILURE_EXIT;
    return EXIT_SUCCESS;
}
