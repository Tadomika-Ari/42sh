/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** which
*/

#include "../../include/struct.h"

int display_alias(char *cmd, char *value)
{
    write(1, cmd, my_strlen(cmd));
    write(1, ":\taliased to ", 13);
    write(1, value, my_strlen(value));
    write(1, "\n", 1);
    free(value);
    return SUCCESS_EXIT;
}

int display_built(char *cmd)
{
    write(1, cmd, my_strlen(cmd));
    write(1, " is a shell built in\n", 21);
    return SUCCESS_EXIT;
}

int display_bin(char *cmd, char *value)
{
    write(1, value, my_strlen(value));
    write(1, "\n", 1);
    free(value);
    return SUCCESS_EXIT;
}

int search_cmd(char *cmd, tcsh_t *term)
{
    char *char_tmp = my_strdup(cmd);
    char *value = alias(term, char_tmp);

    if (value == NULL) {
        free(char_tmp);
        return ALT_EXIT;
    }
    if (my_strcmp(value, cmd) != 0)
        return display_alias(cmd, value);
    free(char_tmp);
    value = NULL;
    for (nodes_t *tmp = term->func; tmp; tmp = tmp->next)
        if (my_strcmp(((function_t *)(tmp->data))->name, cmd) == 0)
            return display_built(cmd);
    value = search_bin(term, cmd);
    if (value == NULL)
        return my_cmd_error(": Command not found.\n",
            cmd, ALT_EXIT);
    return display_bin(cmd, value);
}

int my_which(tcsh_t *term, char **argv)
{
    int res = 0;

    if (len_array(argv) < 1)
        return my_cmd_error(": Too few arguments.\n",
            "which", ALT_EXIT);
    for (int i = 0; argv[i] != NULL; i++)
        res = search_cmd(argv[i], term);
    return res;
}
