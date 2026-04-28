/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

static void unlink_job(tcsh_t *term, job_t *prev, job_t *current)
{
    if (prev)
        prev->next = current->next;
    else
        term->jobs = current->next;
    free(current->cmd);
    free(current);
}

void remove_job(tcsh_t *term, job_t *job)
{
    job_t *prev = NULL;
    job_t *current = NULL;

    if (!term || !job)
        return;
    current = term->jobs;
    while (current) {
        if (current->id == job->id && current->pgid == job->pgid) {
            unlink_job(term, prev, current);
            return;
        }
        prev = current;
        current = current->next;
    }
}
