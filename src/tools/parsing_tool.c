/*
** EPITECH PROJECT, 2026
** tool
** File description:
** tool
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
