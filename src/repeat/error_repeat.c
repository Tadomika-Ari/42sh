/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** error_repeat
*/

#include "../../include/struct.h"

int is_only_spaces(const char *cmd)
{
    if (!cmd)
        return 1;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n' && cmd[i] != '\r')
            return 0;
    return 1;
}

int check_error(tcsh_t *term, char *cmd, int value)
{
    if (my_strlen(cmd) == 2) {
        printf("repeat: Too few arguments\n");
        free(cmd);
        return FAILURE_EXIT;
    }
    if (fail_repeat_check(term, cmd, value) == FAILURE_EXIT) {
        term->error_repeat++;
        free(cmd);
        return FAILURE_EXIT;
    }
    return SUCCESS_EXIT;
}

int fail_repeat_check(tcsh_t *term, char *cmd, int value)
{
    char **temp = NULL;

    temp = my_str_to_word_array(cmd, " ");
    if (len_array(temp) == 2 || len_array(temp) == 1) {
        printf("repeat: Too few arguments\n");
        term->error_repeat++;
        free_array(temp);
        return FAILURE_EXIT;
    }
    if (atoi(temp[1]) == 0) {
        free_array(temp);
        return FAILURE_EXIT;
    }
    free_array(temp);
    return SUCCESS_EXIT;
}
