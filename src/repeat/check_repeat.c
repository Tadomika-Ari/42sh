/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** check_repeat
*/

#include "../../include/struct.h"

int check_repeat(char *av, tcsh_t *term)
{
    char **tmp = NULL;
    int repeat_nb = 0;

    if (av == NULL)
        return FAILURE_EXIT;
    tmp = my_str_to_word_array(av, " ");
    if (tmp == NULL || tmp[0] == NULL || tmp[1] == NULL) {
        free_array(tmp);
        return FAILURE_EXIT;
    }
    if (strcmp("repeat", tmp[0]) == 0) {
        repeat_nb = atoi(tmp[1]);
        term->nb_repeat = repeat_nb;
        term->nb_nb_repeat = my_lenbase(repeat_nb, 10);
        term->is_repeat = TRUE;
    }
    free_array(tmp);
    return SUCCESS_EXIT;
}

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
