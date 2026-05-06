/*
** EPITECH PROJECT, 2026
** tools_alias
** File description:
** tools_alias
*/

#include "../../include/struct.h"

void free_alias_history(nodes_t *alias_histo)
{
    nodes_t *next = NULL;

    for (nodes_t *current = alias_histo; current != NULL; current = next) {
        next = current->next;
        free(current->data);
        free(current);
    }
}

alias_t init_alias(char *cmd)
{
    alias_t tmp;

    tmp.new_expanded = NULL;
    tmp.expanded = cmd;
    tmp.prev_first_word = NULL;
    tmp.curr_first_word = NULL;
    tmp.alias_histo = NULL;
    return tmp;
}

void *ret_error_alias(alias_t *tmp)
{
    free_alias_history(tmp->alias_histo);
    free(tmp->new_expanded);
    free(tmp->prev_first_word);
    free(tmp->curr_first_word);
    return my_puterror_ptr("Alias loop.\n");
}

void free_prev_cur(char *prev, char *cur)
{
    free(prev);
    free(cur);
}
