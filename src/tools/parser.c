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

static int is_sep_token(char c, char *sep)
{
    if (is_sep(c, sep) == TRUE)
        return TRUE;
    for (int i = 0; SEP[i] != '\0'; i++) {
        if (SEP[i] == c)
            return TRUE;
    }
    return FALSE;
}

int check_char(char *str, int i, parse_t *parse, char *sep)
{
    if (str[i] == '$') {
        parse->in_var = TRUE;
        return FALSE;
    }
    if (parse->in_var == TRUE && is_sep_token(str[i], sep) == TRUE) {
        parse->in_var = FALSE;
        return TRUE;
    }
    if (is_sep(str[i], sep) == TRUE)
        return TRUE;
    return FALSE;
}

static int is_quote(char c)
{
    return (c == '"' || c == '\'');
}

static int should_split_on_quote(parse_t *parse, char c, int start)
{
    return (!parse->in_quote && !parse->in_tick && is_quote(c)
        && parse->i > start);
}

static int nb_element(char *str, char *sep)
{
    int i = 0;
    int start = 0;
    parse_t parse = {0};
    int count = 0;

    while (str[i]) {
        if (should_split_on_quote(&parse, str[i], start)) {
            count += (i > start) ? 1 : 0;
            start = i;
        }
        update_state(&parse, str[i]);
        if (!is_protected(&parse) && check_char(str, i, &parse, sep) == TRUE) {
            count += (i > start) ? 1 : 0;
            start = i + 1;
        }
        i++;
        parse.i = i;
    }
    count += (i > start) ? 1 : 0;
    return count;
}

static void copy_next(parse_t *parse, char *str, char **res, int num)
{
    char *next = NULL;

    if (parse->i > parse->start) {
        next = strndup(&str[parse->start], parse->i - parse->start);
        res[parse->count] = next;
        parse->count++;
    }
    parse->start = parse->i + num;
}

char **parser3000(char *str, char *sep)
{
    char **res = NULL;
    parse_t parse = {0};

    res = malloc(sizeof(char *) * (nb_element(str, sep) + 1));
    if (!res)
        return NULL;
    while (str[parse.i]) {
        if (should_split_on_quote(&parse, str[parse.i], parse.start))
            copy_next(&parse, str, res, 0);
        update_state(&parse, str[parse.i]);
        if (!is_protected(&parse) && is_sep(str[parse.i], sep))
            copy_next(&parse, str, res, 1);
        parse.i++;
    }
    copy_next(&parse, str, res, 0);
    res[parse.count] = NULL;
    if (correct_tab(res) == FALSE)
        return NULL;
    return res;
}
