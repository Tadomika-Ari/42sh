/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** where
*/

#include "../../include/struct.h"

static void display_all_alias(char *cmd, tcsh_t *term)
{
    char *char_tmp = my_strdup(cmd);
    char *value = alias(term, char_tmp);

    if (value == NULL) {
        free(char_tmp);
        return;
    }
    if (my_strcmp(value, cmd) != 0) {
        display_alias(cmd, value);
        return;
    }
    free(char_tmp);
}

void display_all_built(char *cmd, tcsh_t *term)
{
    for (nodes_t *tmp = term->func; tmp; tmp = tmp->next)
        if (my_strcmp(((function_t *)(tmp->data))->name, cmd) == 0)
            display_built(cmd);
}

void search_in_file(char *path, char *command)
{
    DIR *bin = opendir(path);

    if (!bin)
        return;
    for (struct dirent *dir = readdir(bin); dir; dir = readdir(bin)) {
        if (my_strcmp(dir->d_name, command) == 0) {
            write(1, path, strlen(path));
            write(1, "/", 1);
            write(1, command, my_strlen(command));
            write(1, "\n", 1);
            closedir(bin);
            return;
        }
    }
    closedir(bin);
}

void display_all_bin(char *cmd, tcsh_t *term)
{
    nodes_t *path = search_node(term->env, "PATH");
    char **bin = NULL;

    if (!path)
        bin = my_str_to_word_array("/usr/bin:/bin:/usr/local/bin", ":=\n");
    else
        bin = my_str_to_word_array(path->data, ":=\n");
    if (!bin)
        return;
    for (int i = 0; bin[i]; i++)
        search_in_file(bin[i], cmd);
    free_array(bin);
}

void search_all_cmd(char *cmd, tcsh_t *term)
{
    display_all_alias(cmd, term);
    display_all_built(cmd, term);
    display_all_bin(cmd, term);
}

int my_where(tcsh_t *term, char **argv)
{
    if (len_array(argv) < 1)
        return my_cmd_error(": Too few arguments.\n",
            "where", ALT_EXIT);
    for (int i = 0; argv[i] != NULL; i++)
        search_all_cmd(argv[i], term);
    return SUCCESS_EXIT;
}
