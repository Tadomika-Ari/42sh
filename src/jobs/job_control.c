/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control
*/

#include "../../include/struct.h"

char *is_job_control(parse_t *parse,char *cmd, int i)
{
    if (!is_protected(parse) && (cmd[i] == '&' && cmd[i + 1] == '&'))
        return "&&";
    if (!is_protected(parse) && (cmd[i] == '|' && cmd[i + 1] == '|'))
        return "||";
    return NULL;
}

int job_detection(char *cmd)
{
    parse_t parse = {0};

    for (int i = 0; cmd[i] != '\0'; i++) {
        update_state(&parse, cmd[i]);
        if (is_job_control(&parse, cmd, i) != NULL)
            return TRUE;
    }
    return FALSE;
}

int job_control(tcsh_t *term, char *cmd)
{
    if (job_detection(cmd) == TRUE)

        else
            choose_command(term, cmd);
}
