/*
** EPITECH PROJECT, 2026
** history
** File description:
** history
*/

#include "../../include/struct.h"

static nodes_t *init_node_history(char *cmd, int index)
{
    nodes_t *node = malloc(sizeof(nodes_t));
    history_t *tmp = NULL;

    if (node == NULL)
        return NULL;
    tmp = malloc(sizeof(history_t));
    if (tmp == NULL) {
        free(node);
        return NULL;
    }
    tmp->cmd = my_strdup(cmd);
    tmp->index = index;
    tmp->time = my_strdup("9:03");
    node->data = (void *)tmp;
    return node;
}

int push_to_history(tcsh_t *term, char *cmd)
{
    nodes_t *tmp = NULL;

    term->len_history++;
    tmp = init_node_history(cmd, term->len_history);
    if (tmp == NULL)
        return FAILURE_EXIT;
    push_back(&term->history, tmp);
    return SUCCESS_EXIT;
}

static void print_struc_history(history_t *tmp)
{
    my_put_nbr(tmp->index);
    write(1, "  ", 2);
    write(1, tmp->cmd, my_strlen(tmp->cmd));
}

int my_history(tcsh_t *term, char **cmd)
{
    history_t *info = NULL;

    for (nodes_t *current = term->history; current != NULL;
        current = current->next) {
        info = current->data;
        print_struc_history(info);
    }
    return SUCCESS_EXIT;
}
