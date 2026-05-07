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

int repeat_or_no_repeat(tcsh_t *term, char *cmd, int value)
{
    char *expanded = NULL;
    char *copy_cmd = NULL;

    cmd[strcspn(cmd, "\n")] = '\0';
    if (is_only_spaces(cmd)) {
        free(cmd);
        return 0;
    }
    for (int i = 0; i < term->nb_repeat - 1 && term->is_repeat == TRUE; i++) {
        copy_cmd = my_strdup(cmd);
        expanded = alias(term, copy_cmd);
        if (expanded == NULL)
            return 0;
        loops_multi_func(term, expanded, value);
    }
    expanded = alias(term, cmd);
    if (expanded == NULL)
        return 0;
    return loops_multi_func(term, expanded, value);
}
