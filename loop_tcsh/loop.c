/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** loop
*/

#include "../include/struct.h"

static int is_only_spaces(const char *cmd)
{
    if (!cmd)
        return 1;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n' && cmd[i] != '\r')
            return 0;
    return 1;
}

int filter_command(tcsh_t *term, int value)
{
    char *cmd = NULL;
    char **tmp = NULL;
    int return_value = value;

    if (user_entry(term, &cmd) == FAILURE_EXIT || term->life == DEAD)
        return -1;
    if (is_only_spaces(cmd)) {
        free(cmd);
        return 0;
    }
    tmp = my_str_to_word_array(cmd, ";");
    for (int i = 0; tmp[i] != NULL; i++) {
        return_value = choose_command(term, tmp[i]);
        if (return_value == FAILURE_EXIT)
            return FAILURE_EXIT;
    }
    free_array(tmp);
    free(cmd);
    return return_value;
}

int running(tcsh_t *term)
{
    int return_value = FAILURE_EXIT;
    int tmp = 0;

    while (term->life == LIFE) {
        tmp = filter_command(term, return_value);
        if (tmp == -1)
            break;
        return_value = tmp;
        if (return_value == FAILURE_EXIT)
            break;
    }
    free_all(term);
    return return_value;
}

int my_sh(char **env)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));

    if (!term)
        return FAILURE_EXIT;
    if (init(term, env) == FAILURE_EXIT) {
        free(term);
        return FAILURE_EXIT;
    }
    return running(term);
}
