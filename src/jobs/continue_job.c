/*
** EPITECH PROJECT, 2026
** job
** File description:
** job
*/

#include "../../include/struct.h"
#include <signal.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

static int wait_foreground_group(pid_t pgid, int *status)
{
    pid_t w = 0;

    do {
        w = waitpid(-pgid, status, WUNTRACED);
    } while (w > 0 && !WIFEXITED(*status) &&
        !WIFSIGNALED(*status) && !WIFSTOPPED(*status));
    return (w == -1) ? FAILURE_EXIT : SUCCESS_EXIT;
}

int continue_job_fg(tcsh_t *term, job_t *job)
{
    int status = 0;

    if (!term || !job)
        return FAILURE_EXIT;
    if (tcsetpgrp(STDIN_FILENO, job->pgid) == -1)
        return FAILURE_EXIT;
    term->fg_pgid = job->pgid;
    if (kill(-job->pgid, SIGCONT) == -1) {
        tcsetpgrp(STDIN_FILENO, term->shell_pgid);
        term->fg_pgid = 0;
        return FAILURE_EXIT;
    }
    job->state = RUNNING;
    if (wait_foreground_group(job->pgid, &status) == FAILURE_EXIT) {
        tcsetpgrp(STDIN_FILENO, term->shell_pgid);
        term->fg_pgid = 0;
        return FAILURE_EXIT;
    }
    tcsetpgrp(STDIN_FILENO, term->shell_pgid);
    term->fg_pgid = 0;
    if (WIFSTOPPED(status))
        job->state = STOPPED;
    else {
        job->state = DONE;
        remove_job(term, job);
    }
    return SUCCESS_EXIT;
}

int continue_job_bg(tcsh_t *term, job_t *job)
{
    if (!term || !job)
        return FAILURE_EXIT;
    if (kill(-job->pgid, SIGCONT) == -1)
        return FAILURE_EXIT;
    job->state = RUNNING;
    dprintf(STDOUT_FILENO, "[%d] %d %s\n", job->id, job->pgid, job->cmd);
    return SUCCESS_EXIT;
}
