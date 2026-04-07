/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** other_error_message
*/

#include "../include/struct.h"

int error_alphanumeric(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Variable name must contain alphanumeric characters.\n", 54);
    return ALTERNATIVE_EXIT;
}

int error_not_a_directory(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Not a directory.\n", 19);
    return ALTERNATIVE_EXIT;
}

int argument_not_support(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Argument not supported.\n", 26);
    return ALTERNATIVE_EXIT;
}

int error_no_home(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": No home directory.\n", 21);
    return ALTERNATIVE_EXIT;
}

int error_permission_denied(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Permission denied.\n", 21);
    return ALTERNATIVE_EXIT;
}
