/*
** EPITECH PROJECT, 2026
** add_alias.c
** File description:
** add_alias
*/

#include "../../include/struct.h"

static int check_tab(char **tab, char *buf_rc)
{
    if (tab == NULL)
        return FAILURE_EXIT;
    if (tab[0] == NULL) {
        free_array(tab);
        free(buf_rc);
        return SUCCESS_EXIT;
    }
    return 42;
}

int print_alias(tcsh_t *term)
{
    nodes_t *current = term->alias;
    alias_t *info = NULL;

    if (current == NULL)
        return SUCCESS_EXIT;
    for (; current != NULL; current = current->next) {
        info = current->data;
        if (info != NULL)
            printf("%s  %s\n", info->name_alias, info->cmd_alias);
    }
    return SUCCESS_EXIT;
}

alias_t *init_alias(char *name, char *cmd)
{
    alias_t *tmp = malloc(sizeof(alias_t));

    if (tmp == NULL)
        return my_puterror_ptr("ERROR Malloc alias");
    tmp->name_alias = my_strdup(name);
    tmp->cmd_alias = my_strdup(cmd);
    return tmp;
}

static char *creat_single_str(char **cmd)
{
    char *cmd_alias = NULL;
    int len = 0;

    for (int i = 1; cmd[i] != NULL; i++)
        len += (my_strlen(cmd[i]) + 1);
    cmd_alias = malloc(sizeof(char) * (len + 1));
    if (cmd_alias == NULL)
        return NULL;
    cmd_alias[0] = '\0';
    for (int i = 1; cmd[i] != NULL; i++) {
        my_strcat(cmd_alias, cmd[i]);
        if (cmd[i + 1] != NULL)
            my_strcat(cmd_alias, " ");
    }
    return cmd_alias;
}

static nodes_t *init_node_alias(char **cmd, nodes_t *new)
{
    alias_t *new_alias = NULL;
    char *cmd_alias = NULL;

    cmd_alias = creat_single_str(cmd);
    if (cmd_alias == NULL)
        return NULL;
    new_alias = init_alias(cmd[0], cmd_alias);
    if (new_alias == NULL) {
        free(cmd_alias);
        return NULL;
    }
    free(cmd_alias);
    new->data = new_alias;
    return new;
}

static int get_unique_alias(tcsh_t *term, char *cmd)
{
    char *alias_cmd = NULL;

    alias_cmd = check_alias(term, cmd);
    if (alias_cmd != NULL) {
        printf("%s\n", alias_cmd);
        free(alias_cmd);
    }
    return SUCCESS_EXIT;
}

int my_alias(tcsh_t *term, char **cmd)
{
    nodes_t *node = NULL;

    if (cmd[0] == NULL)
        return print_alias(term);
    if (cmd[1] == NULL)
        return get_unique_alias(term, cmd[0]);
    if (my_strcmp("alias", cmd[0]) == 0)
        return put_err("alias: Too dangerous to alias that.\n",
            ALTERNATIVE_EXIT);
    node = malloc(sizeof(nodes_t));
    if (node == NULL)
        return put_err("ERROR malloc node_alias\n", FAILURE_EXIT);
    push_front(&term->alias, init_node_alias(cmd, node));
    return SUCCESS_EXIT;
}
