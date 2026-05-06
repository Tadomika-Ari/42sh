/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** job_control
*/

#include "../../include/struct.h"
#include "../../lib/my/my.h"

char *is_job_control(parse_t *parse, char *cmd, int i)
{
    if (!is_protected(parse) && (cmd[i] == '&' && cmd[i + 1] == '&'))
        return "&&";
    if (!is_protected(parse) && (cmd[i] == '|' && cmd[i + 1] == '|'))
        return "||";
    return NULL;
}

int len_job_cmd(char *cmd)
{
    parse_t parse = {0};
    int nb = 0;
    for (int i = 0; cmd[i] != '\0'; i++) {
        update_state(&parse, cmd[i]);
        if (is_job_control(&parse, cmd, i) != NULL) {
            nb = nb + 1;
            i = i + 1;
        }
    }
    return nb;
}

void job_cmd_splitting(char *cmd, char **commands, char **jobs)
{
    parse_t parse = {0};
    int position = 0;
    int nb_cmd = 0;
    char *separators = NULL;

    for (int i = 0; cmd[i] != '\0'; i++){
        update_state(&parse, cmd[i]);
        separators = is_job_control(&parse, cmd, i);
        if (separators != NULL){
            commands[nb_cmd] = strndup(cmd + position, i - position);
            jobs[nb_cmd] = separators;
            position = i + 2;
            nb_cmd++;
            i++;
        }
    }
    commands[nb_cmd] = strndup(cmd + position, my_strlen(cmd) - position);
    commands[nb_cmd + 1] = NULL;
    jobs[nb_cmd ] = NULL;
}

int job_detection(char *cmd)
{
    parse_t parse = {0};

    for (int i = 0; cmd[i] != '\0'; i++) {
        update_state(&parse, cmd[i]);
        if (is_job_control(&parse, cmd, i) != NULL)
            return TRUE;
    }
    return FALSE;
}

int job_control(tcsh_t *term, char *cmd)
{
    char **commands = malloc(sizeof(char *) * (len_job_cmd(cmd) + 2));
    char **jobs = malloc(sizeof(char *) * (len_job_cmd(cmd) + 1));

    if (job_detection(cmd) == TRUE) {
        job_cmd_splitting(cmd, commands, jobs);
    }
    free_array(commands);
    free_array(jobs);
    return choose_command(term, cmd);
}