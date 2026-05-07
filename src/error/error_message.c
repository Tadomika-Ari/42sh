/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_message
*/

#include "../../include/struct.h"

int path_not_found(char *path)
{
    write(1, path, my_strlen(path));
    return put_err(": No such file or directory.\n", ALTERNATIVE_EXIT);
}

int error_too_many_argument(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(TOO_MANY, ALTERNATIVE_EXIT);
}

int error_not_enough_argument(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(TOO_FEW, ALTERNATIVE_EXIT);
}

int error_expression_syntax(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(EXPRESSION_SYNTAX, ALTERNATIVE_EXIT);
}

static int error_glob_match(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(NO_MATCH, ALTERNATIVE_EXIT);
}

int command_not_found(char *cmd)
{
    if (is_globing(cmd) == TRUE)
        return error_glob_match(cmd);
    write(1, cmd, my_strlen(cmd));
    return put_err(CMD_NOT_FOUND, 1);
}
