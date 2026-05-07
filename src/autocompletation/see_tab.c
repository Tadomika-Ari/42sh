/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** see_tab
*/

#include "../../include/struct.h"

static void clear_current_input(int len, int cursor_pos)
{
    if (cursor_pos > 0)
        move_left(cursor_pos);
    for (int i = 0; i < len; i++)
        write(1, " ", 1);
    move_left(len);
}

int final_step(getline_t *st_g, tcsh_t *term, int idx, int new_len)
{
    int old_len = st_g->line_len;
    int old_cursor = term->whereiscursor;

    st_g->line_len = new_len;
    term->whereiscursor = st_g->line_len;
    term->maxposcursor = st_g->line_len;
    clear_current_input(old_len, old_cursor);
    write(1, st_g->line, my_strlen(st_g->line));
    term->pos_tab = idx + 1;
    if (term->pos_tab > term->maxpos_tab)
        term->pos_tab = 0;
    return SUCCESS_EXIT;
}

int init_see_tab(tcsh_t *term, int *count, int *idx)
{
    *count = len_array(term->result_tab);
    if (*count == 0) {
        term->statut_tab = 0;
        return FAILURE_EXIT;
    }
    term->maxpos_tab = *count - 1;
    *idx = term->pos_tab;
    if (*idx < 0 || *idx > term->maxpos_tab)
        *idx = 0;
    return SUCCESS_EXIT;
}

int see_tab(tcsh_t *term, getline_t *st_g)
{
    char *result = NULL;
    int new_len = 0;
    int count = 0;
    int idx = 0;

    if (init_see_tab(term, &count, &idx) == FAILURE_EXIT)
        return FAILURE_EXIT;
    result = my_strdup(term->result_tab[idx]);
    if (!result)
        return FAILURE_EXIT;
    new_len = my_strlen(result);
    if (ensure_capacity(&st_g->line, &st_g->cap, new_len) == -1) {
        free(result);
        return FAILURE_EXIT;
    }
    memcpy(st_g->line, result, new_len + 1);
    final_step(st_g, term, idx, new_len);
    free(result);
    return SUCCESS_EXIT;
}
