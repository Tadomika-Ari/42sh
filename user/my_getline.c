/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** my_getline
*/

#include "../include/struct.h"
#include <termios.h>

#define INITIAL_CAPACITY 128

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

static int handle_escape_sequence(void)
{
    char seq[2] = {0};

    if (read(STDIN_FILENO, &seq[0], 1) <= 0)
        return 0;
    if (read(STDIN_FILENO, &seq[1], 1) <= 0)
        return 0;
    if (seq[0] != '[')
        return 0;
    if (seq[1] == 'A')
        printf("debug: fleche haut\n");
    if (seq[1] == 'B')
        printf("debug: fleche bas\n");
    return 0;
}

int my_getline(char **cmd, size_t *len)
{
    struct termios old_t = {0};
    struct termios raw_t = {0};
    size_t cap = (len && *len > 0) ? *len : INITIAL_CAPACITY;
    size_t line_len = 0;
    char *line = NULL;
    char c = 0;
    ssize_t rd = 0;

    if (!isatty(STDIN_FILENO))
        return getline(cmd, len, stdin);
    line = malloc(cap);
    if (!line)
        return -1;
    line[0] = '\0';
    if (tcgetattr(STDIN_FILENO, &old_t) == -1) {
        free(line);
        return getline(cmd, len, stdin);
    }
    raw_t = old_t;
    raw_t.c_lflag &= ~(ICANON | ECHO);
    raw_t.c_cc[VMIN] = 1;
    raw_t.c_cc[VTIME] = 0;
    if (tcsetattr(STDIN_FILENO, TCSANOW, &raw_t) == -1) {
        free(line);
        return getline(cmd, len, stdin);
    }
    while (1) {
        rd = read(STDIN_FILENO, &c, 1);
        if (rd <= 0) {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
            free(line);
            return -1;
        }
        if (c == '\n' || c == '\r') {
            write(STDOUT_FILENO, "\n", 1);
            break;
        }
        if (c == 4 && line_len == 0) {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
            free(line);
            return -1;
        }
        if ((c == 127 || c == 8) && line_len > 0) {
            line_len--;
            line[line_len] = '\0';
            write(STDOUT_FILENO, "\b \b", 3);
            continue;
        }
        if (c == 27) {
            handle_escape_sequence();
            continue;
        }
        if (!isprint((unsigned char)c))
            continue;
        if (ensure_capacity(&line, &cap, line_len + 1) == -1) {
            tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
            free(line);
            return -1;
        }
        line[line_len] = c;
        line_len++;
        line[line_len] = '\0';
        write(STDOUT_FILENO, &c, 1);
    }
    tcsetattr(STDIN_FILENO, TCSANOW, &old_t);
    if (ensure_capacity(&line, &cap, line_len + 1) == -1) {
        free(line);
        return -1;
    }
    line[line_len] = '\n';
    line[line_len + 1] = '\0';
    free(*cmd);
    *cmd = line;
    if (len)
        *len = cap;
    return (int)(line_len + 1);
}
