/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** other_error_message
*/

#include "../../include/struct.h"

int error_alphanumeric(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Variable name must contain alphanumeric characters.\n",
        ALTERNATIVE_EXIT);
}

int error_not_a_directory(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Not a directory.\n", ALTERNATIVE_EXIT);
}

int argument_not_support(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Argument not supported.\n", ALTERNATIVE_EXIT);
}

int error_no_home(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": No home directory.\n", ALTERNATIVE_EXIT);
}

int error_permission_denied(char *cmd)
{
    put_err(cmd, SUCCESS_EXIT);
    return put_err(": Permission denied.\n", ALTERNATIVE_EXIT);
}
