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

    if (term == NULL || cmd == NULL)
        return FAILURE_EXIT;
    if (my_strcmp(cmd, "!!\n") == 0)
        return SUCCESS_EXIT;
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

int my_last_cmd(tcsh_t *termn, char **cmd)
{
    history_t *tmp = NULL;
    nodes_t *current = NULL;

    if (termn == NULL || termn->history == NULL) {
        printf("0: Event not found.\n");
        return FAILURE_EXIT;
    }
    current = termn->history;
    while (current->next != NULL)
        current = current->next;
    if (current->data != NULL) {
        tmp = current->data;
        printf("%s", tmp->cmd);
        return choose_command(termn, tmp->cmd);
    } else {
        printf("0: Event not found.\n");
        return FAILURE_EXIT;
    }
}

int my_history(tcsh_t *term, char **cmd)
{
    history_t *info = NULL;

    if (term == NULL)
        return FAILURE_EXIT;
    for (nodes_t *current = term->history; current != NULL;
        current = current->next) {
        info = current->data;
        if (info == NULL)
            continue;
        print_struc_history(info);
    }
    return SUCCESS_EXIT;
}
