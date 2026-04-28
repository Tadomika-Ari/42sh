/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** cursor_move
*/

#include "../../include/struct.h"

int insert_char_at_cursor(getline_t *st_g, tcsh_t *term)
{
    size_t tail_len = 0;

    if (ensure_capacity(&st_g->line, &st_g->cap, st_g->line_len + 1) == -1)
        return return_reset(st_g);
    memmove(st_g->line + term->whereiscursor + 1,
        st_g->line + term->whereiscursor,
        st_g->line_len - term->whereiscursor + 1);
    st_g->line[term->whereiscursor] = st_g->c;
    st_g->line_len++;
    term->whereiscursor++;
    term->maxposcursor++;
    tail_len = st_g->line_len - term->whereiscursor;
    write(STDOUT_FILENO, st_g->line + term->whereiscursor - 1, tail_len + 1);
    move_left(tail_len);
    return SUCCESS_EXIT;
}

int delete_char_before_cursor(getline_t *st_g, tcsh_t *term)
{
    size_t tail_len = 0;

    if (term->whereiscursor <= 0)
        return 0;
    term->whereiscursor--;
    memmove(st_g->line + term->whereiscursor,
        st_g->line + term->whereiscursor + 1,
        st_g->line_len - term->whereiscursor);
    st_g->line_len--;
    term->maxposcursor--;
    write(STDOUT_FILENO, "\x1b[D", 3);
    tail_len = st_g->line_len - term->whereiscursor;
    if (tail_len > 0)
        write(STDOUT_FILENO, st_g->line + term->whereiscursor, tail_len);
    write(STDOUT_FILENO, " ", 1);
    move_left(tail_len + 1);
    return 0;
}

void move_left(size_t count)
{
    for (size_t i = 0; i < count; i++)
        write(STDOUT_FILENO, "\x1b[D", 3);
}

int ensure_capacity(char **line, size_t *cap, size_t wanted)
{
    char *tmp = NULL;

    if (wanted + 1 < *cap)
        return 0;
    while (wanted + 1 >= *cap)
        *cap *= 2;
    tmp = realloc(*line, *cap);
    if (!tmp)
        return -1;
    *line = tmp;
    return 0;
}

int return_reset(getline_t *st_g)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &st_g->old_t);
    free(st_g->line);
    return -1;
}
