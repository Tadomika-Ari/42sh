/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_message
*/

#include "../include/struct.h"

int path_not_found(char *path)
{
    write(1, path, my_strlen(path));
    write(1, ": No such file or directory.\n", 29);
    return ALTERNATIVE_EXIT;
}

int error_too_many_argument(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Too many arguments.\n", 22);
    return ALTERNATIVE_EXIT;
}

int error_not_enough_argument(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Too few arguments.\n", 21);
    return ALTERNATIVE_EXIT;
}

int error_expression_syntax(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Expression Syntax.\n", 21);
    return ALTERNATIVE_EXIT;
}

int command_not_found(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Command not found.\n", 21);
    return ALTERNATIVE_EXIT;
}
