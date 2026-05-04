/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_message
*/

#include "../../include/struct.h"

int path_not_found(char *path)
{
    put_err(path, SUCCESS_EXIT);
    return put_err(": No such file or directory.\n", ALTERNATIVE_EXIT);
}

int error_too_many_argument(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Too many arguments.\n", ALTERNATIVE_EXIT);
}

int error_not_enough_argument(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Too few arguments.\n", ALTERNATIVE_EXIT);
}

int error_expression_syntax(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Expression Syntax.\n", ALTERNATIVE_EXIT);
}

static int error_glob_match(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": No match.\n", ALTERNATIVE_EXIT);
}

int command_not_found(char *cmd)
{
    if (is_globing(cmd) == TRUE)
        return error_glob_match(cmd);
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Command not found.\n", ALTERNATIVE_EXIT);
}
