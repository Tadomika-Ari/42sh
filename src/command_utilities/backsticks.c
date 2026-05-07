/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** backsticks
*/

#include <unistd.h>
#include <sys/wait.h>

#include "../../include/struct.h"

int get_fd_command(tcsh_t *term, char *command, int fd[2])
{
    int pid = 0;
    int res = 0;

    if (pipe(fd) != 0)
        return ALTERNATIVE_EXIT;
    pid = fork();
    if (pid == 0) {
        close(fd[0]);
        dup2(fd[1], STDOUT_FILENO);
        close(fd[1]);
        exit(loops_multi_func(term, my_strdup(command),
                atoi(term->return_value)));
    }
    close(fd[1]);
    waitpid(pid, &res, 0);
    if (!WIFEXITED(res) || WEXITSTATUS(res) != 0) {
        close(fd[0]);
        return ALTERNATIVE_EXIT;
    }
    return SUCCESS_EXIT;
}

char *del_par(char *str)
{
    int len = my_strlen(str);
    char *res = malloc((len - 1) * sizeof(char));

    if (!res)
        return NULL;
    for (int i = 1; i < len - 1; i++)
        res[i - 1] = str[i];
    res[len - 2] = '\0';
    return res;
}

char *backsticks(tcsh_t *term, char *command)
{
    char *line = del_par(command);
    int fd[2] = {-1, -1};

    if (!line)
        return NULL;
    if (get_fd_command(term, line, fd) != SUCCESS_EXIT) {
        free(line);
        return NULL;
    }
    free(line);
    return read_fd(fd);
}
