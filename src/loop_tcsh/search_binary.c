/*
** EPITECH PROJECT, 2026
** bin
** File description:
** bin
*/

#include "../../include/struct.h"

char *search_bin(tcsh_t *term, char *command)
{
    nodes_t *path = search_node(term->env, "PATH");
    char **bin = NULL;
    char *lign = NULL;

    if (!path)
        bin = my_str_to_word_array("/usr/bin:/bin:/usr/local/bin", ":=\n");
    else
        bin = my_str_to_word_array(path->data, ":=\n");
    if (!bin)
        return NULL;
    for (int i = 0; bin[i]; i++) {
        lign = search_binary(bin[i], command);
        if (lign != NULL)
            break;
    }
    free_array(bin);
    return lign;
}

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
