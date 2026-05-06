/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** loop
*/

#include "../../include/struct.h"
#include <sys/wait.h>

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
    char *repeat_cmd = NULL;

    if (user_entry(term, &cmd) == FAILURE_EXIT || term->life == DEAD)
        return -1;
    if (strncmp(cmd, "repeat ", 7) == 0 || strncmp(cmd, "repeat", 6) == 0) {
        term->nb_nb_repeat = 0;
        check_repeat(cmd, term);
        if (check_error(term, cmd, value) == FAILURE_EXIT)
            return ALTERNATIVE_EXIT;
        repeat_cmd = cut_len(cmd, 7 + term->nb_nb_repeat);
        free(cmd);
        cmd = repeat_cmd;
        if (cmd == NULL)
            return ALTERNATIVE_EXIT;
    }
    return repeat_or_no_repeat(term, cmd, value);
}

char *int_to_str(int n)
{
    int len = snprintf(NULL, 0, "%d", n);
    char *s = malloc(len + 1);

    if (!s)
        return NULL;
    snprintf(s, len + 1, "%d", n);
    return s;
}

int running(tcsh_t *term)
{
    int return_value = FAILURE_EXIT;
    int tmp = 0;

    while (term->life == LIFE) {
        reap_jobs(term);
        tmp = filter_command(term, return_value);
        term->is_repeat = FALSE;
        term->error_repeat = 0;
        if (tmp == -1)
            break;
        return_value = tmp;
        if (return_value == FAILURE_EXIT)
            break;
        if (term->return_value)
            free(term->return_value);
        term->return_value = int_to_str(return_value);
    }
    free_all(term);
    return return_value;
}

int my_sh(char **env)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    if (!term)
        return FAILURE_EXIT;
    if (init(term, env) == FAILURE_EXIT) {
        free(term);
        return FAILURE_EXIT;
    }
    return running(term);
}
