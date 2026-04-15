/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** init
*/

#include "../include/struct.h"

nodes_t *create_new_node(char *lign_env)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    if (!new)
        return NULL;
    new->data = my_strdup(lign_env);
    if (!new->data) {
        free(new);
        return NULL;
    }
    return new;
}

static int get_env(tcsh_t *term, char **env)
{
    nodes_t *new = NULL;

    for (int i = 0; env[i] != NULL; i++) {
        new = create_new_node(env[i]);
        if (!new)
            return FAILURE_EXIT;
        push_back(&term->env, new);
    }
    return SUCCESS_EXIT;
}

static int push_function(tcsh_t *term,
    int (*cmd)(tcsh_t *, char **), const char *name)
{
    nodes_t *new = malloc(sizeof(nodes_t));

    if (!new)
        return FAILURE_EXIT;
    new->data = malloc(sizeof(function_t));
    if (!new->data) {
        free(new);
        return FAILURE_EXIT;
    }
    ((function_t *)new->data)->name = name;
    ((function_t *)new->data)->cmd = *cmd;
    push_front(&term->func, new);
    return SUCCESS_EXIT;
}

static int fill_function(tcsh_t *term)
{
    if (push_function(term, my_cd, "cd") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, env, "env") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, my_setenv, "setenv") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, my_unsetenv, "unsetenv") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, my_exit, "exit") == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (push_function(term, my_history, "history") == FAILURE_EXIT)
        return FAILURE_EXIT;
    return SUCCESS_EXIT;
}

int init(tcsh_t *term, char **env)
{
    if (!env)
        return FAILURE_EXIT;
    term->env = NULL;
    term->func = NULL;
    term->life = LIFE;
    term->old = NULL;
    term->history = NULL;
    term->len_history = 0;
    if (get_env(term, env) == FAILURE_EXIT)
        return FAILURE_EXIT;
    if (fill_function(term) == FAILURE_EXIT)
        return FAILURE_EXIT;
    return SUCCESS_EXIT;
}
