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

static void edit_list(nodes_t *list, int index)
{
    int i = 0;
    char **res = NULL;

    for (nodes_t *current = list; current; current = current->next) {
        res = translate(current->data);
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

char **sweeper(char *str)
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
    edit_list(list, 2);
    tab = node_to_array(list);
    free_list(list);
    return tab;
}
