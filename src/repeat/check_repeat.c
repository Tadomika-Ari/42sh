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

    if (av == NULL)
        return FAILURE_EXIT;
    tmp = my_str_to_word_array(av, " ");
    if (strncmp("repeat", tmp[0], 5) == 0) {
        term->nb_repeat = atoi(tmp[1]);
        term->is_repeat = TRUE;
        printf("ITS OK : %d\n", term->nb_repeat);
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

int array_len_char(char *cmd)
{
    int i = 0;
    int count = 0;
    int in_word = 0;

    if (!cmd)
        return 0;
    while (cmd[i] != '\0') {
        if (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n' && cmd[i] != '\r') {
            if (in_word == 0) {
                count++;
                in_word = 1;
            }
        } else {
            in_word = 0;
        }
        i++;
    }
    return count;
}
