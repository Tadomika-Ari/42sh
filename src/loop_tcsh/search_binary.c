/*
** EPITECH PROJECT, 2026
** bin
** File description:
** bin
*/

#include "../../include/struct.h"

char *search_binary(char *path, char *command)
{
    DIR *bin = opendir(path);
    char *result = NULL;

    if (!bin)
        return result;
    for (struct dirent *dir = readdir(bin); dir; dir = readdir(bin)) {
        if (my_strcmp(dir->d_name, command) == 0) {
            result = assembling(path, "/", (char *[]){command, NULL});
            closedir(bin);
            return result;
        }
    }
    closedir(bin);
    return result;
}
