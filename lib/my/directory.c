/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** directory
*/

#include "my.h"

int is_it_directory(char *path)
{
    struct stat stat_file;

    if (!path)
        return 0;
    if (stat(path, &stat_file) == -1)
        return 0;
    return S_ISDIR(stat_file.st_mode);
}
