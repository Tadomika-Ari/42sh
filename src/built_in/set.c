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

static char *take_name(char *var)
{
    char **tmp = my_str_to_word_array(var, "=");
    char *res = NULL;

    if (tmp == NULL)
        return NULL;
    if (correct_name(tmp[0], "set") != SUCCESS_EXIT) {
        free_array(tmp);
        return NULL;
    }
    res = my_strdup(tmp[0]);
    free_array(tmp);
    return res;
}

int single_value(tcsh_t *term, char *var)
{
    locals_t *local = malloc(sizeof(locals_t));

    if (local == NULL)
        return -1;
    local->name = take_name(var);
    local->value = NULL;
    if (local->name == NULL) {
        free(local);
        return -1;
    }
    for (int i = 0; var[i]; i++) {
        if (var[i] == '=') {
            local->value = var[i + 1] != '\0' ? my_strdup(&var[i + 1]) : NULL;
            break;
        }
    }
    insert(term, local);
    return 1;
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
        return 1;
    }
    if (argv[1] != NULL && argv[2] != NULL) {
        local->value = my_strdup(argv[2]);
        res += 1;
    }
    insert(term, local);
    return res;
}

int correct_var(char *name, char *cmd)
{
    if ((name[0] < 'a' || name[0] > 'z') &&
        (name[0] < 'A' || name[0] > 'Z') && name[0] != '_')
        return ALTERNATIVE_EXIT;
    if (my_str_name(name) != 0)
        return ALTERNATIVE_EXIT;
    return SUCCESS_EXIT;
}

static int display(tcsh_t *term)
{
    for (nodes_t *tmp = term->locals; tmp; tmp = tmp->next) {
        write(1, ((locals_t *)tmp->data)->name, my_strlen(((locals_t *)tmp->data)->name));
        if (((locals_t *)tmp->data)->value) {
            write(1, "\t", 1);
            write(1, ((locals_t *)tmp->data)->value, my_strlen(((locals_t *)tmp->data)->value));
        }
        write(1, "\n", 1);
    }
    return SUCCESS_EXIT;
}

int my_set(tcsh_t *term, char **argv)
{
    int tmp = 0;

    if (len_array(argv) == 0)
        return display(term);
    for (int i = 0; argv[i];) {
        if (correct_var(argv[i], "set") != SUCCESS_EXIT) {
            tmp = single_value(term, argv[i]);
            if (tmp == 1) {
                i += tmp;
                continue;
            }
            return ALTERNATIVE_EXIT;
        }
        tmp = add_variable(&argv[i], term);
        if (tmp == -1)
            return ALTERNATIVE_EXIT;
        i += tmp;
    }
    return SUCCESS_EXIT;
}
