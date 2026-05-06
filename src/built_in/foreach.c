/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** foreach
*/

#include "../../include/struct.h"

static char *get_user(char *tmp, bool *error, char **res)
{
    size_t len_w = 0;

    if (getline(&tmp, &len_w, stdin) == -1) {
        *error = true;
        free_array(res);
        return NULL;
    }
    tmp[my_strlen(tmp) - 1] = '\0';
    return tmp;
}

static int add(char ***res, char *tmp, int *len)
{
    *res = realloc(*res, sizeof(char *) * (*len + 2));
    if (*res == NULL) {
        free(tmp);
        return ALTERNATIVE_EXIT;
    }
    (*res)[*len] = my_strdup(tmp);
    (*res)[*len + 1] = NULL;
    if ((*res)[*len] == NULL) {
        free(tmp);
        free_array(*res);
        return ALTERNATIVE_EXIT;
    }
    *len = *len + 1;
    free(tmp);
    return SUCCESS_EXIT;
}

char **take_action(bool *error)
{
    char **res = malloc(sizeof(char *));
    char *tmp = NULL;
    int len = 0;

    if (res == NULL)
        return NULL;
    res[0] = NULL;
    while (1) {
        tmp = get_user(tmp, error, res);
        if (*error == true)
            return NULL;
        if (my_strcmp(tmp, "end") == 0) {
            free(tmp);
            return res;
        }
        if (add(&res, tmp, &len) == ALTERNATIVE_EXIT)
            return NULL;
        tmp = NULL;
    }
}

int from_one_line(tcsh_t *term, char *cmd)
{
    char *repeat_cmd = NULL;

    if (strncmp(cmd, "repeat ", 7) == 0 || strncmp(cmd, "repeat", 6) == 0) {
        term->nb_nb_repeat = 0;
        check_repeat(cmd, term);
        if (check_error(term, cmd, atoi(term->return_value)) == FAILURE_EXIT)
            return ALTERNATIVE_EXIT;
        repeat_cmd = cut_len(cmd, 7 + term->nb_nb_repeat);
        free(cmd);
        cmd = repeat_cmd;
        if (cmd == NULL)
            return ALTERNATIVE_EXIT;
    }
    return repeat_or_no_repeat(term, cmd, atoi(term->return_value));
}

static int execute_all(tcsh_t *term, char **action)
{
    int res = 0;

    for (int i = 0; action[i]; i++) {
        res = from_one_line(term, my_strdup(action[i]));
        if (res != 0)
            return res;
    }
    return res;
}

int in_for(tcsh_t *term, char **argv, bool *error)
{
    char **value = NULL;
    char **action = take_action(error);
    int res = 0;

    if (*error == true)
        return ALTERNATIVE_EXIT;
    value = my_str_to_word_array(argv[1], " ()\n\t");
    for (int i = 0; value[i] != NULL; i++) {
        if (my_set(term, (char *[]){argv[0], "=",
                    value[i], NULL}) != SUCCESS_EXIT) {
            res = ALTERNATIVE_EXIT;
            break;
        }
        res = execute_all(term, action);
        if (res != SUCCESS_EXIT)
            break;
    }
    free_array(value);
    free_array(action);
    return res;
}

int my_foreach(tcsh_t *term, char **argv)
{
    int len = len_array(argv);
    bool error = false;

    if (len < 2)
        return my_cmd_error(":Too few arguments.\n",
            "foreach", ALTERNATIVE_EXIT);
    if (len > 2)
        return my_cmd_error(": Words not parenthesized.\n",
            "foreach", ALTERNATIVE_EXIT);
    if (correct_name(argv[0], "foreach") != SUCCESS_EXIT)
        return ALTERNATIVE_EXIT;
    return in_for(term, argv, &error);
}
