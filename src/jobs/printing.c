/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"

int print_return(int fd, const char *str)
{
    dprintf(fd, "%s", str);
    return ALTERNATIVE_EXIT;
}

int no_such_job(job_t *job, const char *str)
{
    if (!job) {
        dprintf(STDERR_FILENO, "%s", str);
        return ALTERNATIVE_EXIT;
    }
    return EXIT_SUCCESS;
}
