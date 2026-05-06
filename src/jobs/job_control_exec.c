/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control_exec
*/

#include "../../include/struct.h"
#include "../../lib/my/my.h"

static void status_true(jobs_exec_t *status)
{
    status->ignore = TRUE;
    status->or_done = TRUE;
}

static void status_false(jobs_exec_t *status)
{
    status->ignore = FALSE;
    status->or_done = FALSE;
}

int job_execution(tcsh_t *term, jobs_exec_t *sta,
    char **cmds, char **jobs)
{
    if (cmds == NULL || jobs == NULL)
        return FALSE;
    if (empty_error_case(cmds, jobs) == TRUE)
        return SUCCESS_EXIT;
    for (int i = 0; cmds[i] != NULL; i++){
        if (sta->ignore == FALSE && sta->or_done == FALSE
            && empty_cmd_detect(cmds[i]) == FALSE)
            sta->value = choose_command(term, cmds[i]);
        if (jobs[i] != NULL && my_strcmp(jobs[i], "&&") == 0 && sta->value != 0
            || jobs[i] != NULL && my_strcmp(jobs[i], "||") == 0
            && sta->value == 0)
            status_true(sta);
        if (jobs[i] != NULL && my_strcmp(jobs[i], "&&") == 0 && sta->value == 0)
            sta->ignore = FALSE;
        if (jobs[i] != NULL && my_strcmp(jobs[i], "||") == 0 && sta->value != 0)
            status_false(sta);
    }
    return sta->value;
}
