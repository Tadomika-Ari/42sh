/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** is_scripting
*/

#include "../../include/struct.h"
#include <sys/wait.h>
#include <unistd.h>

static int write_all(int fd, const char *str)
{
    size_t len = my_strlen((char *)str);
    ssize_t wr = 0;
    size_t total = 0;

    while (total < len) {
        wr = write(fd, str + total, len - total);
        if (wr <= 0)
            return ALT_EXIT;
        total += (size_t)wr;
    }
    return SUCCESS_EXIT;
}

static int feed_child_stdin(int fd, char **action, pid_t pid)
{
    for (int i = 1; action[i] != NULL; i++) {
        if (write_all(fd, action[i]) != SUCCESS_EXIT ||
            write_all(fd, "\n") != SUCCESS_EXIT) {
            close(fd);
            waitpid(pid, NULL, 0);
            return ALT_EXIT;
        }
    }
    write_all(fd, "exit\n");
    close(fd);
    return SUCCESS_EXIT;
}

static int wait_child_status(pid_t pid)
{
    int status = 0;

    if (waitpid(pid, &status, 0) == -1)
        return ALT_EXIT;
    if (WIFEXITED(status))
        return WEXITSTATUS(status);
    return ALT_EXIT;
}

static void run_42sh_child(int in_pipe[2])
{
    dup2(in_pipe[0], STDIN_FILENO);
    close(in_pipe[0]);
    close(in_pipe[1]);
    execl("./42sh", "./42sh", NULL);
    _exit(1);
}

static int run_42sh_with_stdin(char **action)
{
    int in_pipe[2] = {0, 0};
    pid_t pid = 0;

    if (pipe(in_pipe) == -1)
        return ALT_EXIT;
    pid = fork();
    if (pid == -1) {
        close(in_pipe[0]);
        close(in_pipe[1]);
        return ALT_EXIT;
    }
    if (pid == 0)
        run_42sh_child(in_pipe);
    close(in_pipe[0]);
    if (feed_child_stdin(in_pipe[1], action, pid) != SUCCESS_EXIT)
        return ALT_EXIT;
    return wait_child_status(pid);
}

int in_action(char **action, tcsh_t *term)
{
    if (strstr(action[0], "./42sh") == NULL) {
        free_array(action);
        return ALT_EXIT;
    }
    term->script = run_42sh_with_stdin(action);
    free_array(action);
    return -67;
}

int is_scripting(tcsh_t *term, char **command)
{
    char **action = NULL;

    if (len_array(command) != 1)
        return ALT_EXIT;
    action = get_buffer(command[0], "\n");
    if (action == NULL)
        return ALT_EXIT;
    if (action[0] == NULL) {
        free(action);
        return ALT_EXIT;
    }
    return in_action(action, term);
}
