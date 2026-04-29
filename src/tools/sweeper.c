/*
** EPITECH PROJECT, 2026
** sweepe
** File description:
** sweeper
*/

#include "../../include/struct.h"

static void replace(char **tab, nodes_t *list, nodes_t *next)
{
    nodes_t *current = list;

    list->next = NULL;
    for (int i = 1; tab[i] != NULL; i++) {
        push_back(&list, create_new_node(tab[i]));
        free(tab[i]);
    }
    while (current->next)
        current = current->next;
    current->next = next;
}

static int is_translatable(char *str)
{
    if (is_inihbitor(str) == TRUE)
        return FALSE;
    if (is_parenthesis(str) == TRUE)
        return FALSE;
    return TRUE;
}

static void edit_list(tcsh_t *term, nodes_t *list, int index)
{
    int i = 0;
    char **res = NULL;

    for (nodes_t *current = list; current; current = current->next) {
        res = translate(term, current);
        free(current->data);
        current->data = res[0];
        replace(res, current, current->next);
        free(res);
        i++;
    }
}

static void free_list(nodes_t *list)
{
    nodes_t *next = NULL;

    for (nodes_t *current = list; current != NULL; current = next) {
        next = current->next;
        free(current);
    }
}

static void remove_background_operator(char **tab)
{
    int len = 0;

    if (!tab)
        return;
    len = len_array(tab);
    if (len > 0 && my_strcmp(tab[len - 1], "&") == 0) {
        free(tab[len - 1]);
        tab[len - 1] = NULL;
    }
}

char **sweeper(tcsh_t *term, char *str)
{
    char **tab = parser3000(str, "\n \t");
    nodes_t *list = NULL;

    if (!tab)
        return NULL;
    list = array_to_node(tab);
    if (!list) {
        free_array(tab);
        return NULL;
    }
    free_array(tab);
    edit_list(term, list, 2);
    tab = node_to_array(list);
    free_list(list);
    remove_background_operator(tab);
    return tab;
}
