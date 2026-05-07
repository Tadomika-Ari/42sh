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
    return put_err(": Variable name must contain alphanumeric characters.\n",
        ALT_EXIT);
}

int error_not_a_directory(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": Not a directory.\n", ALT_EXIT);
}

int argument_not_support(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": Argument not supported.\n", ALT_EXIT);
}

int error_no_home(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": No home directory.\n", ALT_EXIT);
}

int error_permission_denied(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": Permission denied.\n", ALT_EXIT);
}
