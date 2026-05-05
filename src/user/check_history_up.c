/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** check_history
*/

#include "../../include/struct.h"

static void clear_current_input(size_t len)
{
    for (size_t i = 0; i < len; i++)
        write(1, "\b", 1);
    for (size_t i = 0; i < len; i++)
        write(1, " ", 1);
    for (size_t i = 0; i < len; i++)
        write(1, "\b", 1);
}

int history_init(tcsh_t *term, getline_t *st_g, nodes_t *node)
{
    if (term == NULL || st_g == NULL || node == NULL)
        return 84;
    if (term->len_history <= 0)
        return 84;
    if (st_g->statut_history >= term->len_history)
        st_g->statut_history = term->len_history - 1;
    term->check_history = 1;
    return 0;
}

int history_end(tcsh_t *term, size_t *old_len, getline_t *st_g, history_t *tmp)
{
    free(st_g->line);
    clear_current_input(*old_len);
    st_g->cap = st_g->len_u + 2;
    st_g->line = malloc(sizeof(char) * st_g->cap);
    if (st_g->line == NULL)
        return 84;
    for (size_t i = 0; i < st_g->len_u; i++)
        st_g->line[i] = tmp->cmd[i];
    st_g->line[st_g->len_u] = '\0';
    st_g->line_len = st_g->len_u;
    term->maxposcursor = st_g->line_len;
    term->whereiscursor = st_g->line_len;
    write(1, st_g->line, st_g->line_len);
    st_g->statut_history++;
    return 0;
}

int check_history_up(tcsh_t *term, getline_t *st_g)
{
    nodes_t *node = term->history;
    history_t *tmp = NULL;
    size_t old_len = 0;
    int target = 0;

    st_g->len_u = 0;
    if (history_init(term, st_g, node) == 84)
        return 0;
    target = term->len_history - st_g->statut_history - 1;
    for (int i = 0; node != NULL && i < target; i++)
        node = node->next;
    if (node == NULL || node->data == NULL)
        return 0;
    tmp = node->data;
    old_len = st_g->line_len;
    st_g->len_u = all_for_len(term, tmp);
    if (st_g->len_u > 0 && tmp->cmd[st_g->len_u - 1] == '\n')
        st_g->len_u--;
    history_end(term, &old_len, st_g, tmp);
    return 0;
}
