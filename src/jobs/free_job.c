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

    while (jobs) {
        next = jobs->next;
        free(jobs->cmd);
        free(jobs);
        jobs = next;
    }
}
