/*
** EPITECH PROJECT, 2026
** special_variable
** File description:
** my_cwd
*/

#include "../../include/struct.h"

int my_cwd(tcsh_t *term, char **cmd)
{
    char *path = getcwd(NULL, 0);

    write(1, path, my_strlen(path));
    write(1, "\n", 1);
    if (path != NULL)
        free(path);
    return SUCCESS_EXIT;
}
