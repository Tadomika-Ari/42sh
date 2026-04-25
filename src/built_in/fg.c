/*
** EPITECH PROJECT, 2026
** fg
** File description:
** fg
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

static job_t *last_job(job_t *jobs)
{
    job_t *last = NULL;

    for (; jobs; jobs = jobs->next)
        last = jobs;
    return last;
}

int my_fg(tcsh_t *term, char **argv)
{
    job_t *job = NULL;
    int id = 0;

    if (!term || !term->jobs)
        return print_return(STDERR_FILENO, "fg: No current job.\n");
    if (argv && argv[0]) {
        if (argv[1])
            return print_return(STDERR_FILENO, "fg: usage: fg [%%job]\n");
        if (parse_job_id(argv[0], &id) == FAILURE_EXIT) {
            dprintf(STDERR_FILENO, "fg: %s: invalid job id.\n", argv[0]);
            return ALTERNATIVE_EXIT;
        }
        job = find_job_id(term, id);
    } else
        job = last_job(term->jobs);
    if (no_such_job(job, "fg: No such job.\n") == ALTERNATIVE_EXIT)
        return ALTERNATIVE_EXIT;
    return continue_job_fg(term, job);
}
