/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** exit
*/

#include "../../include/struct.h"

void insert(tcsh_t *term, locals_t *local)
{
    for (nodes_t *tmp = term->locals; tmp; tmp = tmp->next) {
        if (my_strcmp(((locals_t *)tmp->data)->name, local->name) == 0) {
            free_locals(tmp->data);
            tmp->data = local;
            return;
        }
    }
    push_front(&term->locals, new_node(local));
}

int add_variable(char **argv, tcsh_t *term)
{
    int res = 1;
    locals_t *local = malloc(sizeof(locals_t));

    if (!local)
        return -1;
    local->name = my_strdup(argv[0]);
    local->value = NULL;
    if (argv[1] != NULL && strcmp(argv[1], "=") == 0)
        res += 1;
    else {
        push_front(&term->locals, new_node(local));
        return res;
    }
    if (argv[1] != NULL && argv[2] != NULL) {
        local->value = my_strdup(argv[2]);
        res += 1;
    }
    insert(term, local);
    return res;
}

int my_set(tcsh_t *term, char **argv)
{
    for (int i = 0; argv[i];) {
        if (correct_name(argv[i], "set") != SUCCESS_EXIT)
            return ALTERNATIVE_EXIT;
        i += add_variable(&argv[i], term);
    }
    return SUCCESS_EXIT;
}
