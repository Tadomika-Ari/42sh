/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** bonus
*/

#include "../../include/struct.h"

void print_letter_hangman(hang_t *hang)
{
    printf("%s\n", ASK_LETTER);
    for (int r = 0; r < NB_ROW; r++)
        printf("%s\n", STEPS[10 - hang->hp][r]);
}
