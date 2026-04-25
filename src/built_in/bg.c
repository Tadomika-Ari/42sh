/*
** EPITECH PROJECT, 2026
** bg
** File description:
** bg
*/

#include "../../include/struct.h"
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

static int parse_job_id(char *arg, int *id)
{
    char *end = NULL;

    if (!arg || !id)
        return FAILURE_EXIT;
    if (arg[0] == '%')
        arg++;
    if (arg[0] == '\0')
        return FAILURE_EXIT;
    *id = (int)strtol(arg, &end, 10);
    if (!end || *end != '\0' || *id <= 0)
        return FAILURE_EXIT;
    return SUCCESS_EXIT;
}

static job_t *last_stopped_or_last(job_t *jobs)
{
    job_t *last = NULL;
    job_t *stopped = NULL;

    for (; jobs; jobs = jobs->next) {
        last = jobs;
        if (jobs->state == STOPPED)
            stopped = jobs;
    }
    return stopped ? stopped : last;
}

int my_bg(tcsh_t *term, char **argv)
{
    job_t *job = NULL;
    int id = 0;

    if (!term || !term->jobs)
        return print_return(STDERR_FILENO, "bg: No current job.\n");
    if (argv && argv[0]) {
        if (argv[1])
            return print_return(STDERR_FILENO, "bg: usage: bg [%%job]\n");
        if (parse_job_id(argv[0], &id) == FAILURE_EXIT) {
            dprintf(STDERR_FILENO, "bg: %s: invalid job id.\n", argv[0]);
            return ALTERNATIVE_EXIT;
        }
        job = find_job_id(term, id);
    } else
        job = last_stopped_or_last(term->jobs);
    if (no_such_job(job, "bg: No such job.\n") == ALTERNATIVE_EXIT)
        return ALTERNATIVE_EXIT;
    return continue_job_bg(term, job);
}
