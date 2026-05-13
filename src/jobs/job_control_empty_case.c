/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control_empty_case
*/

#include "../../include/struct.h"
#include "../../lib/my/my.h"

int empty_cmd_detect(char *cmd)
{
    if (cmd == NULL)
        return TRUE;
    for (int i = 0; cmd[i] != '\0'; i++){
        if (cmd[i] != ' ' && cmd[i] != '\t')
            return FALSE;
    }
    return TRUE;
}

int empty_cmd_and(char *job)
{
    if (job != NULL && my_strcmp(job, "&&") == 0)
        return FALSE;
    return my_cmd_error(NULL_CMD, "", TRUE);
}

int empty_error_case(char **commands, char **jobs)
{
    int cmd_count = 0;

    for (int i = 0; commands[i] != NULL; i++){
        if (empty_cmd_detect(commands[i]) == FALSE)
            cmd_count = 1;
        if (empty_cmd_detect(commands[i]) == TRUE && cmd_count == TRUE){
            return my_cmd_error(NULL_CMD, "", TRUE);
        }
        if (empty_cmd_detect(commands[i]) == TRUE && cmd_count == FALSE
            && empty_cmd_and(jobs[i]) == TRUE)
            return TRUE;
    }
    return FALSE;
}
