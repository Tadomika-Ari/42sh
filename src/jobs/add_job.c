/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

int get_max_job_id(tcsh_t *term)
{
    job_t *tmp = NULL;
    int max = 0;

    if (!term)
        return 0;
    tmp = term->jobs;
    for (; tmp; tmp = tmp->next)
        if (tmp->id > max)
            max = tmp->id;
    return max;
}

void add_job(tcsh_t *term, pid_t pgid, char *cmd, job_state_t state)
{
    job_t *new_job = NULL;
    job_t *tmp = NULL;

    if (!term || !cmd)
        return;
    new_job = malloc(sizeof(job_t));
    if (!new_job)
        return;
    new_job->cmd = my_strdup(cmd);
    if (!new_job->cmd) {
        free(new_job);
        return;
    }
    new_job->pgid = pgid;
    new_job->state = state;
    new_job->id = get_max_job_id(term) + 1;
    new_job->next = NULL;
    if (!term->jobs) {
        term->jobs = new_job;
        return;
    }
    tmp = term->jobs;
    for (; tmp->next; tmp = tmp->next);
    tmp->next = new_job;
}
