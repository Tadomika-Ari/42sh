/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control
*/

#include "../../include/struct.h"
#include "../../lib/my/my.h"

static void free_cmd_jobs(char **commands, char **jobs)
{
    free_array(commands);
    free(jobs);
}

static char *is_job_control(parse_t *parse, char *cmd, int i)
{
    if (!is_protected(parse) && (cmd[i] == '&' && cmd[i + 1] == '&'))
        return "&&";
    if (!is_protected(parse) && (cmd[i] == '|' && cmd[i + 1] == '|'))
        return "||";
    return NULL;
}

static int len_job_cmd(char *cmd)
{
    parse_t parse = {0};
    int nb = 0;

    if (cmd == NULL)
        return 0;
    for (int i = 0; cmd[i] != '\0'; i++) {
        update_state(&parse, cmd[i]);
        if (is_job_control(&parse, cmd, i) != NULL) {
            nb = nb + 1;
            i = i + 1;
        }
    }
    return nb;
}

int fill_commands_jobs(jobs_cont_t *counts, char *cmd,
    char **commands, char **jobs)
{
    commands[counts->nb_cmd] = strndup(cmd + counts->position,
        counts->i - counts->position);
    if (commands[counts->nb_cmd] == NULL)
        return ALTERNATIVE_EXIT;
    jobs[counts->nb_cmd] = counts->separators;
    counts->position = counts->i + 2;
    counts->nb_cmd++;
    return SUCCESS_EXIT;
}

static int handle_separators(jobs_cont_t *counts, char *cmd,
    char **commands, char **jobs)
{
    if (counts->separators == NULL)
        return SUCCESS_EXIT;
    if (fill_commands_jobs(counts, cmd, commands, jobs) == ALTERNATIVE_EXIT)
        return ALTERNATIVE_EXIT;
    counts->i++;
    return SUCCESS_EXIT;
}

int job_cmd_splitting(jobs_cont_t *counts, char *cmd,
    char **commands, char **jobs)
{
    parse_t parse = {0};

    if (cmd == NULL || commands == NULL || jobs == NULL)
        return FAILURE_EXIT;
    for (counts->i = 0; cmd[counts->i] != '\0'; counts->i++){
        update_state(&parse, cmd[counts->i]);
        counts->separators = is_job_control(&parse, cmd, counts->i);
        if (handle_separators(counts, cmd, commands, jobs) == ALTERNATIVE_EXIT)
            return ALTERNATIVE_EXIT;
    }
    commands[counts->nb_cmd] = strndup(cmd + counts->position,
        my_strlen(cmd) - counts->position);
    if (commands[counts->nb_cmd] == NULL)
        return FAILURE_EXIT;
    commands[counts->nb_cmd + 1] = NULL;
    jobs[counts->nb_cmd] = NULL;
    return SUCCESS_EXIT;
}

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
    for (int i = 0; cmds[i] != NULL; i++){
        if (sta->ignore == FALSE && sta->or_done == FALSE)
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

int handle_splitting_error(char *cmd, char **commands, char **jobs)
{
    jobs_cont_t counts = {0};

    if (job_cmd_splitting(&counts, cmd, commands, jobs) == FAILURE_EXIT){
        free_cmd_jobs(commands, jobs);
        return ALTERNATIVE_EXIT;
    }
    return SUCCESS_EXIT;
}

int job_control(tcsh_t *term, char *cmd)
{
    jobs_exec_t status = {0};
    char **commands = NULL;
    char **jobs = NULL;
    int value = 0;

    if (cmd == NULL)
        return FAILURE_EXIT;
    commands = malloc(sizeof(char *) * (len_job_cmd(cmd) + 2));
    jobs = malloc(sizeof(char *) * (len_job_cmd(cmd) + 1));
    if (commands == NULL)
        return FAILURE_EXIT;
    if (jobs == NULL){
        free(commands);
        return FAILURE_EXIT;
    }
    if (handle_splitting_error(cmd, commands, jobs) == ALTERNATIVE_EXIT)
        return ALTERNATIVE_EXIT;
    value = job_execution(term, &status, commands, jobs);
    free_cmd_jobs(commands, jobs);
    return value;
}
