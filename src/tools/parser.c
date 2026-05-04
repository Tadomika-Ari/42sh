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
    return (c == '"' || c == '\'');
}

static int should_split_on_quote(parse_t *parse, char c, int start)
{
    return (!parse->in_quote && !parse->in_tick && is_quote(c)
        && parse->i > start);
}

void update_ele(ele_t *ele)
{
    if (ele->i > ele->start)
        ele->count++;
    ele->start = ele->i;
}

void count_element(parse_t *parse, char *sep, char *str, ele_t *ele)
{
    if (!parse->in_quote && !parse->in_tick && str[parse->i] == '$') {
        update_ele(ele);
        parse->in_var = TRUE;
    }
    if (should_split_on_quote(parse, str[ele->i], ele->start))
        update_ele(ele);
    update_state(parse, str[ele->i]);
    if (!is_protected(parse) && parse->in_var == TRUE && str[ele->i] == '}') {
        ele->count += (ele->i >= ele->start) ? 1 : 0;
        ele->start = ele->i + 1;
        parse->in_var = FALSE;
    } else if (!is_protected(parse)
        && check_char(str, ele->i, parse, sep) == TRUE) {
        ele->count += (ele->i > ele->start) ? 1 : 0;
        ele->start = ele->i + 1;
    }
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
    if (!parse->in_quote && !parse->in_tick && str[parse->i] == '$') {
        if (parse->i > parse->start)
            copy_next(parse, str, res, 0);
        parse->start = parse->i;
        parse->in_var = TRUE;
    }
    if (should_split_on_quote(parse, str[parse->i], parse->start))
        copy_next(parse, str, res, 0);
    update_state(parse, str[parse->i]);
    if (!is_protected(parse) && parse->in_var == TRUE
        && str[parse->i] == '}') {
        parse->in_var = FALSE;
        parse->i++;
        copy_next(parse, str, res, 0);
        return;
    }
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
