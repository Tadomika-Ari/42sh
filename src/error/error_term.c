/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** error_term
*/

#include "../../include/struct.h"

int error_syntax(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": Exec format error. Binary file not executable.\n",
        ALT_EXIT);
}

int error_first_caracter(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(": Variable name must begin with a letter.\n",
        ALT_EXIT);
}

int error_ambigious(void)
{
    return put_err("Ambiguous output redirect.\n", ALT_EXIT);
}

int error_null(void)
{
    return put_err("Invalid null command.\n", ALT_EXIT);
}
