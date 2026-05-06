/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control
*/

#include "../../include/struct.h"
#include "../../lib/my/my.h"

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

void job_cmd_splitting(char *cmd, char **commands, char **jobs)
{
    parse_t parse = {0};
    int position = 0;
    int nb_cmd = 0;
    char *separators = NULL;

    if (cmd == NULL || commands == NULL || jobs == NULL)
        return;
    for (int i = 0; cmd[i] != '\0'; i++){
        update_state(&parse, cmd[i]);
        separators = is_job_control(&parse, cmd, i);
        if (separators != NULL){
            commands[nb_cmd] = strndup(cmd + position, i - position);
            jobs[nb_cmd] = separators;
            position = i + 2;
            nb_cmd++;
            i++;
        }
    }
    commands[nb_cmd] = strndup(cmd + position, my_strlen(cmd) - position);
    commands[nb_cmd + 1] = NULL;
    jobs[nb_cmd] = NULL;
}

int job_execution(tcsh_t *term, char **commands, char **jobs)
{
    int ignore = 0;
    int or_done = 0;
    int value = 0;

    if (commands == NULL || jobs == NULL)
        return FAILURE_EXIT;
    for (int i = 0; commands[i] != NULL; i++){
        if (ignore == FALSE && or_done == FALSE)
            value = choose_command(term, commands[i]);
        if (jobs[i] != NULL && my_strcmp(jobs[i], "&&") == 0 && value != 0
            || jobs[i] != NULL && my_strcmp(jobs[i], "||") == 0 && value == 0){
            ignore = TRUE;
            or_done = TRUE;
        }
        if (jobs[i] != NULL && my_strcmp(jobs[i], "&&") == 0 && value == 0)
            ignore = FALSE;
        if (jobs[i] != NULL && my_strcmp(jobs[i], "||") == 0 && value != 0) {
            ignore = FALSE;
            or_done = FALSE;
        }
    }
    return value;
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
    job_cmd_splitting(cmd, commands, jobs);
    value = job_execution(term, commands, jobs);
    free_array(commands);
    free(jobs);
    return value;
}
