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
    return put_err(EXEC_FORMAT,
        ALTERNATIVE_EXIT);
}

int error_first_caracter(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    return put_err(VAR_NAME,
        ALTERNATIVE_EXIT);
}

int error_ambigious(void)
{
    return put_err("Ambiguous output redirect.\n", ALTERNATIVE_EXIT);
}

int error_null(void)
{
    return put_err("Invalid null command.\n", ALTERNATIVE_EXIT);
}
