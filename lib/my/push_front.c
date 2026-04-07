/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** push_front
*/

#include "my.h"

void push_front(nodes_t **old, nodes_t *new)
{
    new->next = *old;
    *old = new;
}
