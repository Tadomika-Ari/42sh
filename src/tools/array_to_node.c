/*
** EPITECH PROJECT, 2026
** array
** File description:
** node
*/

#include "../../include/struct.h"

int is_sep(char c, char *sep)
{
    for (int i = 0; sep[i] != '\0'; i++) {
        if (sep[i] == c) {
            return TRUE;
        }
    }
    return FALSE;
}

void show_array(char **tab)
{
    if (!tab)
        return;
    for (int i = 0; tab[i] != NULL; i++) {
        printf("%d %s\n", i, tab[i]);
    }
}

nodes_t *array_to_node(char **array)
{
    nodes_t *list = NULL;

    if (!array | !array[0])
        return NULL;
    for (int i = 0; array[i] != NULL; i++) {
        push_back(&list, create_new_node(array[i]));
    }
    return list;
}
