/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_term
*/

#include "../include/struct.h"

int error_syntax(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Exec format error. Binary file not executable.\n", 49);
    return ALTERNATIVE_EXIT;
}

int error_first_caracter(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ": Variable name must begin with a letter.\n", 42);
    return ALTERNATIVE_EXIT;
}

int error_ambigious(void)
{
    write(1, "Ambiguous output redirect.\n", 27);
    return ALTERNATIVE_EXIT;
}

int error_null(void)
{
    write(1, "Invalid null command.\n", 22);
    return ALTERNATIVE_EXIT;
}
