/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** free_all
*/

#include "../../include/struct.h"

void free_locals(locals_t *locals)
{
    if (locals != NULL) {
        if (locals->name)
            free(locals->name);
        if (locals->value)
            free(locals->value);
        free(locals);
    }
}

void free_node_locals(nodes_t *head)
{
    nodes_t *forward = NULL;

    if (!head)
        return;
    forward = head;
    while (head != NULL) {
        forward = forward->next;
        if (head->data)
            free_locals(head->data);
        free(head);
        head = forward;
    }
}

void free_node(nodes_t *head)
{
    nodes_t *forward = NULL;

    if (!head)
        return;
    forward = head;
    while (head != NULL) {
        forward = forward->next;
        if (head->data)
            free(head->data);
        free(head);
        head = forward;
    }
}

static void free_history(history_t *history)
{
    if (history != NULL && history->cmd != NULL)
        free(history->cmd);
    if (history != NULL && history->time != NULL)
        free(history->time);
    if (history != NULL)
        free(history);
}

static void free_node_history(nodes_t *head)
{
    nodes_t *forward = NULL;

    if (!head)
        return;
    forward = head;
    while (head != NULL) {
        forward = forward->next;
        if (head->data)
            free_history(head->data);
        free(head);
        head = forward;
    }
}

void my_free_exist(void *pointer)
{
    if (pointer)
        free(pointer);
}

static void my_free_alias_node(nodes_t *alias)
{
    nodes_t *forward = NULL;
    alias_t *info = NULL;

    if (!alias)
        return;
    forward = alias;
    while (alias != NULL) {
        forward = alias->next;
        if (alias->data) {
            info = alias->data;
            my_free_exist(info->cmd_alias);
            my_free_exist(info->name_alias);
            my_free_exist(info);
        }
        free(alias);
        alias = forward;
    }
}

void free_all(tcsh_t *term)
{
    if (!term)
        return;
    free(term->return_value);
    free_node(term->env);
    free_node_locals(term->locals);
    free_node(term->func);
    my_free_alias_node(term->alias);
    free_node_history(term->history);
    close(term->fd_rc);
    if (term->old)
        free(term->old);
    free_jobs(term->jobs);
    free(term);
}
