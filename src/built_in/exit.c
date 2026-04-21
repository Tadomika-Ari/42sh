/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** exit
*/

#include "../../include/struct.h"

int my_exit(tcsh_t *term, char **argv)
{
    if (len_array(argv) > 1)
        return error_expression_syntax(argv[0]);
    term->life = DEAD;
    write(1, "exit\n", 5);
    return SUCCESS_EXIT;
}
