/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** my_getline
*/

#include "../../include/struct.h"
#include <termios.h>

static int ensure_capacity(char **line, size_t *cap, size_t wanted)
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

static int handle_escape_sequence(tcsh_t *term, getline_t *st_g)
{
    char seq[2] = {0};

    if (read(STDIN_FILENO, &seq[0], 1) <= 0)
        return 0;
    if (read(STDIN_FILENO, &seq[1], 1) <= 0)
        return 0;
    if (seq[0] != '[')
        return 0;
    if (seq[1] == 'A')
        check_history_up(term, st_g);
    if (seq[1] == 'B')
        check_history_down(term, st_g);
    return 0;
}

getline_t init_my_getline(char **cmd, size_t *len)
{
    getline_t st_g = {0};

    st_g.cap = (len && *len > 0) ? *len : INITIAL_CAPACITY;
    st_g.line_len = 0;
    st_g.line = NULL;
    st_g.c = 0;
    st_g.rd = 0;
    st_g.statut_getline = TRUE;
    st_g.statut_echo = 0;
    st_g.statut_exit_getline = 0;
    st_g.statut_history = 0;
    return st_g;
}

static int return_reset(getline_t *st_g)
{
    tcsetattr(STDIN_FILENO, TCSANOW, &st_g->old_t);
    free(st_g->line);
    return -1;
}

static void set_terminal_start(getline_t *st_g)
{
    st_g->raw_t = st_g->old_t;
    st_g->raw_t.c_lflag &= ~(ICANON | ECHO);
    st_g->raw_t.c_cc[VMIN] = 1;
    st_g->raw_t.c_cc[VTIME] = 0;
}

static int loop_getline_final(getline_t *st_g)
{
    if (!isprint((unsigned char)st_g->c))
        return 0;
    if (ensure_capacity(&st_g->line, &st_g->cap,
            st_g->line_len + 1) == -1)
        return return_reset(st_g);
    st_g->line[st_g->line_len] = st_g->c;
    st_g->line_len++;
    st_g->line[st_g->line_len] = '\0';
    write(STDOUT_FILENO, &st_g->c, 1);
    return SUCCESS_EXIT;
}

static int loop_getline(getline_t *st_g, tcsh_t *term)
{
    st_g->rd = read(STDIN_FILENO, &st_g->c, 1);
    if (st_g->rd <= 0)
        return return_reset(st_g);
    if (st_g->c == '\n' || st_g->c == '\r') {
        write(STDOUT_FILENO, "\n", 1);
        st_g->statut_getline = FALSE;
    }
    if (st_g->c == 4 && st_g->line_len == 0)
        return return_reset(st_g);
    if ((st_g->c == 127 || st_g->c == 8) && st_g->line_len > 0) {
        st_g->line_len--;
        st_g->line[st_g->line_len] = '\0';
        write(STDOUT_FILENO, "\b \b", 3);
        return 0;
    }
    if (st_g->c == 27) {
        handle_escape_sequence(term, st_g);
        return 0;
    }
    return loop_getline_final(st_g);
}

static int is_getline(char **cmd, size_t *len)
{
    int rd = 0;

    rd = getline(cmd, len, stdin);
    if (rd == -1) {
        free(*cmd);
        *cmd = NULL;
    }
    return rd;
}

static int loop_st_gart(getline_t *st_g, char **cmd, size_t *len)
{
    if (!isatty(STDIN_FILENO))
        return is_getline(cmd, len);
    st_g->line = malloc(st_g->cap);
    if (!st_g->line)
        return -1;
    st_g->line[0] = '\0';
    if (tcgetattr(STDIN_FILENO, &st_g->old_t) == -1) {
        free(st_g->line);
        return is_getline(cmd, len);
    }
    set_terminal_start(st_g);
    if (tcsetattr(STDIN_FILENO, TCSANOW, &st_g->raw_t) == -1) {
        free(st_g->line);
        return is_getline(cmd, len);
    }
    return SUCCESS_EXIT;
}

int my_getline(char **cmd, size_t *len, tcsh_t *term)
{
    getline_t st_g = init_my_getline(cmd, len);
    int t = loop_st_gart(&st_g, cmd, len);

    if (t != SUCCESS_EXIT)
        return t;
    while (st_g.statut_getline == TRUE) {
        loop_getline(&st_g, term);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &st_g.old_t);
    if (ensure_capacity(&st_g.line, &st_g.cap, st_g.line_len + 1) == -1) {
        free(st_g.line);
        return -1;
    }
    st_g.line[st_g.line_len] = '\n';
    st_g.line[st_g.line_len + 1] = '\0';
    free(*cmd);
    *cmd = st_g.line;
    if (len)
        *len = st_g.cap;
    return (int)(st_g.line_len + 1);
}
