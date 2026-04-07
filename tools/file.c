/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** file
*/

#include "../include/struct.h"

int is_it_file(char *path)
{
    int fd = open(path, O_RDONLY);

    if (fd == -1)
        return 1;
    close(fd);
    return 0;
}
