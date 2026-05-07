/*
** EPITECH PROJECT, 2026
** occ
** File description:
** occ
*/

#include "../../include/struct.h"

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
    if (parse->in_tick == TRUE)
        return FALSE;
    if (parse->in_var == TRUE
        && (is_sep(str[i], sep) == TRUE || str[i] == '"' || str[i] == '\'')) {
        parse->in_var = FALSE;
        return TRUE;
    }
    if (is_sep(str[i], sep) == TRUE)
        return TRUE;
    return FALSE;
}

static int is_quote(char c)
{
    return (c == '"' || c == '\'' || c == '`');
}

static int should_split_on_quote(parse_t *parse, char c, int start)
{
    return (!parse->in_quote && !parse->in_tick && is_quote(c)
        && parse->i > start);
}

void update_parse(parse_t *parse, char *str, char *sep, ele_t *ele)
{
    if (!is_protected(parse) && parse->in_var == TRUE && str[ele->i] == '}') {
        ele->count += (ele->i >= ele->start) ? 1 : 0;
        ele->start = ele->i + 1;
        parse->in_var = FALSE;
    } else if (!is_protected(parse)
        && check_char(str, ele->i, parse, sep) == TRUE) {
        ele->count += (ele->i > ele->start) ? 1 : 0;
        ele->start = ele->i + 1;
    }
}

void count_element(parse_t *parse, char *sep, char *str, ele_t *ele)
{
    if (str[ele->i] == '`') {
        parse->in_tick = !parse->in_tick;
        ele->i++;
        parse->i = ele->i;
        return;
    }
    if (parse->in_tick == TRUE) {
        ele->i++;
        parse->i = ele->i;
        return;
    }
    if (!parse->in_quote && !parse->in_tick && str[parse->i] == '$') {
        update_ele(ele);
        parse->in_var = TRUE;
    }
    update_state(parse, str[ele->i]);
    update_parse(parse, str, sep, ele);
    ele->i++;
    parse->i = ele->i;
}

static int nb_element(char *str, char *sep)
{
    parse_t parse = {0};
    ele_t ele = {0};

    while (str[ele.i]) {
        count_element(&parse, sep, str, &ele);
    }
    ele.count += (ele.i > ele.start) ? 1 : 0;
    return ele.count;
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

void do_parsing(parse_t *parse, char **res, char *str, char *sep)
{
    if (str[parse->i] == '`') {
        parse->in_tick = !parse->in_tick;
        parse->i++;
        return;
    }
    if (parse->in_tick == TRUE) {
        parse->i++;
        return;
    }
    update_state(parse, str[parse->i]);
    if (!is_protected(parse) && is_sep(str[parse->i], sep))
        copy_next(parse, str, res, 1);
    parse->i++;
}

char **parser3000(char *str, char *sep)
{
    char **res = NULL;
    parse_t parse = {0};

    res = malloc(sizeof(char *) * (nb_element(str, sep) + 1));
    if (!res)
        return NULL;
    while (str[parse.i]) {
        do_parsing(&parse, res, str, sep);
    }
    copy_next(&parse, str, res, 0);
    res[parse.count] = NULL;
    if (correct_tab(res) == FALSE)
        return NULL;
    return res;
}
