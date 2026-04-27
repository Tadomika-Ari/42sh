/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** loop
*/

#include "../../include/struct.h"
#include <sys/wait.h>

static int is_only_spaces(const char *cmd)
{
    if (!cmd)
        return 1;
    for (int i = 0; cmd[i] != '\0'; i++)
        if (cmd[i] != ' ' && cmd[i] != '\t' && cmd[i] != '\n' && cmd[i] != '\r')
            return 0;
    return 1;
}

static void reap_jobs(tcsh_t *term)
{
    int status = 0;
    pid_t pid = 0;
    job_t *job = NULL;

    while (1) {
        pid = waitpid(-1, &status, WNOHANG | WUNTRACED | WCONTINUED);
        if (!(pid > 0))
            break;
        job = find_job_pid(term, pid);
        if (!job)
            continue;
        if (WIFEXITED(status) || WIFSIGNALED(status))
            remove_job(term, job);
        if (WIFSTOPPED(status))
            job->state = STOPPED;
        if (WIFCONTINUED(status))
            job->state = RUNNING;
    }
}

int loops_multi_func(tcsh_t *term, char *cmd, int return_value)
{
    char **tmp = NULL;

    tmp = my_str_to_word_array(cmd, ";");
    for (int i = 0; tmp[i] != NULL; i++) {
        return_value = choose_command(term, tmp[i]);
        if (return_value == FAILURE_EXIT)
            return FAILURE_EXIT;
    }
    free_array(tmp);
    free(cmd);
    return return_value;
}

int filter_command(tcsh_t *term, int value)
{
    char *cmd = NULL;

    if (user_entry(term, &cmd) == FAILURE_EXIT || term->life == DEAD)
        return -1;
    if (is_only_spaces(cmd)) {
        free(cmd);
        return 0;
    }
    return loops_multi_func(term, cmd, value);
}

int running(tcsh_t *term)
{
    int return_value = FAILURE_EXIT;
    int tmp = 0;

    while (term->life == LIFE) {
        reap_jobs(term);
        tmp = filter_command(term, return_value);
        if (tmp == -1)
            break;
        return_value = tmp;
        if (return_value == FAILURE_EXIT)
            break;
    }
    free_all(term);
    return return_value;
}

int my_sh(char **env)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));

    if (!term)
        return FAILURE_EXIT;
    if (init(term, env) == FAILURE_EXIT) {
        free(term);
        return FAILURE_EXIT;
    }
    return running(term);
}
