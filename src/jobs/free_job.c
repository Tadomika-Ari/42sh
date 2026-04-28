/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

void free_jobs(job_t *jobs)
{
    job_t *next = NULL;

    for (job_t *cur = jobs; cur; cur = next) {
        next = cur->next;
        if (cur->cmd)
            free(cur->cmd);
        free(cur);
    }
}
