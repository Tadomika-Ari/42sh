/*
** EPITECH PROJECT, 2026
** bouns
** File description:
** bonus
*/

#include "../../include/struct.h"

static char *format_state(job_state_t state)
{
    switch (state) {
        case RUNNING:
            return "RUNNING";
        case STOPPED:
            return "STOPPED";
        case DONE:
            return "DONE";
    }
    return "None";
}

static void print_jobs(job_t *current)
{
    printf("[%d] [PGID: %d] [%s] %s\n",
        current->id, (int)current->pgid,
        format_state(current->state), current->cmd);
}

int jobs(tcsh_t *term, char **argv)
{
    if (!term->jobs)
        return put_err(NO_JOBS, EXIT_FAILURE);
    for (job_t *current = term->jobs; current; current = current->next) {
        print_jobs(current);
    }
    return SUCCESS_EXIT;
}
