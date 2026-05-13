/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_message
*/

#include "../../include/struct.h"

int put_err(char *str, int flags)
{
    write(2, str, my_strlen(str));
    return flags;
}

void *my_puterror_ptr(char *message)
{
    write(2, message, my_strlen(message));
    return NULL;
}

int my_cmd_error(char *str, char *cmd, int out)
{
    write(2, cmd, my_strlen(cmd));
    write(2, str, my_strlen(str));
    return out;
}

static int error_glob_match(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(NO_MATCH, ALT_EXIT);
}

int command_not_found(char *cmd)
{
    if (is_globing(cmd) == TRUE)
        return error_glob_match(cmd);
    write(2, cmd, my_strlen(cmd));
    return put_err(CMD_NOT_FOUND, 1);
}
