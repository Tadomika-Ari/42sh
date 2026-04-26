/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

job_t *find_job_id(tcsh_t *term, int id)
{
    job_t *cur = NULL;

    if (!term)
        return NULL;
    cur = term->jobs;
    while (cur) {
        if (cur->id == id)
            return cur;
        cur = cur->next;
    }
    return NULL;
}

job_t *find_job_pid(tcsh_t *term, pid_t pgid)
{
    job_t *cur = NULL;

    if (!term)
        return NULL;
    cur = term->jobs;
    while (cur) {
        if (cur->pgid == pgid)
            return cur;
        cur = cur->next;
    }
    return NULL;
}
