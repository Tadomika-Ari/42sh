/*
** EPITECH PROJECT, 2026
** occ
** File description:
** occ
*/

#include "../../include/struct.h"

int is_protected(parse_t *parse)
{
    return (parse->in_quote || parse->in_tick
        || parse->parent > 0 || parse->brack > 0);
}

void update_other(parse_t *parse, char c)
{
    if (c == '(')
        parse->parent++;
    if (c == ')')
        parse->parent--;
    if (c == '[')
        parse->brack++;
    if (c == ']')
        parse->brack--;
}

void update_state(parse_t *parse, char c)
{
    if (c == '"' && !parse->in_tick)
        parse->in_quote = !parse->in_quote;
    if (c == '\'' && !parse->in_quote)
        parse->in_tick = !parse->in_tick;
    if (!parse->in_quote && !parse->in_tick)
        update_other(parse, c);
}

int is_sep(char c, char *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (sep[i] == c) {
            return TRUE;
        }
    }
    return FALSE;
}

static int nb_element(char *str, char *sep)
{
    int i = 0;
    int start = 0;
    parse_t parse = {0};
    int count = 0;

    while (str[i]) {
        update_state(&parse, str[i]);
        if (!is_protected(&parse) && is_sep(str[i], sep)) {
            count += (i > start) ? 1 : 0;
            start = i + 1;
        }
        i++;
    }
    count += (i > start) ? 1 : 0;
    return count;
}

static void copy_next(parse_t *parse, char *str, char **res)
{
    char *next = NULL;

    if (parse->i > parse->start) {
        next = strndup(&str[parse->start], parse->i - parse->start);
        res[parse->count] = next;
        parse->count++;
    }
}

char **parser3000(char *str, char *sep)
{
    char **res = NULL;
    parse_t parse = {0};

    res = malloc(sizeof(char *) * (nb_element(str, sep) + 1));
    if (!res)
        return NULL;
    while (str[parse.i]) {
        update_state(&parse, str[parse.i]);
        if (!is_protected(&parse) && is_sep(str[parse.i], sep)) {
            copy_next(&parse, str, res);
            parse.start = parse.i + 1;
        }
        parse.i++;
    }
    copy_next(&parse, str, res);
    res[parse.count] = NULL;
    return res;
}
