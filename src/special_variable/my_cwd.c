/*
** EPITECH PROJECT, 2026
** special_variable
** File description:
** my_cwd
*/

#include "../../include/struct.h"

int my_cwd(tcsh_t *term, char **cmd)
{
    char *path = take_value(term->env, "PWD");

    write(1, path, my_strlen(path));
    write(1, "\n", 1);
    return SUCCESS_EXIT;
}
