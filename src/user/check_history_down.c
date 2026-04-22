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

int history_init_down(tcsh_t *term, getline_t *st_g, nodes_t *node)
{
    if (term == NULL || st_g == NULL || node == NULL)
        return 84;
    if (term->len_history <= 0)
        return 84;
    if (st_g->statut_history >= term->len_history)
        st_g->statut_history = term->len_history - 1;
    if (st_g->statut_history <= 0) {
        if (term->check_history != 0 && term->check_history != 2) {
            term->check_history = 0;
            clear_current_input(st_g->line_len);
            st_g->line_len = 0;
            if (st_g->line != NULL)
                st_g->line[0] = '\0';
        }
        return 84;
    }
    return 0;
}

int history_end_down(size_t *old_len, getline_t *st_g, int len, history_t *tmp)
{
    free(st_g->line);
    clear_current_input(*old_len);
    st_g->cap = len + 2;
    st_g->line = malloc(sizeof(char) * st_g->cap);
    if (st_g->line == NULL)
        return 84;
    for (size_t i = 0; i < len; i++)
        st_g->line[i] = tmp->cmd[i];
    st_g->line[len] = '\0';
    st_g->line_len = len;
    write(1, st_g->line, st_g->line_len);
    st_g->statut_history--;
    return 0;
}

int check_history_down(tcsh_t *term, getline_t *st_g)
{
    nodes_t *node = term->history;
    history_t *tmp = NULL;
    size_t len = 0;
    size_t old_len = 0;
    int target = 0;

    if (history_init_down(term, st_g, node) == 84)
        return 0;
    target = term->len_history - st_g->statut_history;
    for (int i = 0; node != NULL && i < target; i++)
        node = node->next;
    if (node == NULL || node->data == NULL)
        return 0;
    tmp = node->data;
    old_len = st_g->line_len;
    len = my_strlen(tmp->cmd);
    if (len > 0 && tmp->cmd[len - 1] == '\n')
        len--;
    history_end_down(&old_len, st_g, len, tmp);
    return 0;
}
