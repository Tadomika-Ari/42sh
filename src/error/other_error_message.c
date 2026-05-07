/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** other_error_message
*/

#include "../../include/struct.h"

int error_alphanumeric(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(VAR_MUST,
        ALTERNATIVE_EXIT);
}

int error_not_a_directory(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(NOT_DIR, ALTERNATIVE_EXIT);
}

int argument_not_support(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(ARG_NOT_SUP, ALTERNATIVE_EXIT);
}

int error_no_home(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(NO_HOME, ALTERNATIVE_EXIT);
}

int error_permission_denied(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(PERMISSION_DENIED, ALTERNATIVE_EXIT);
}
