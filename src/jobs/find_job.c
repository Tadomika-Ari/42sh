/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

job_t *find_job_id(tcsh_t *term, int id)
{
    job_t *tmp = NULL;

    if (!term)
        return NULL;
    tmp = term->jobs;
    for (; tmp; tmp = tmp->next) {
        if (id == tmp->id)
            return tmp;
    }
    return NULL;
}

job_t *find_job_pid(tcsh_t *term, pid_t pgid)
{
    job_t *tmp = NULL;

    if (!term)
        return NULL;
    tmp = term->jobs;
    for (; tmp; tmp = tmp->next) {
        if (pgid == tmp->pgid)
            return tmp;
    }
    return NULL;
}
