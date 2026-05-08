/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** foreach_tools
*/

#include "../../include/struct.h"

int foreach_is_valid_name(const char *name)
{
    if (!name || !name[0])
        return 0;
    if (!((name[0] >= 'a' && name[0] <= 'z') ||
            (name[0] >= 'A' && name[0] <= 'Z') || name[0] == '_'))
        return 0;
    for (int i = 1; name[i] != '\0'; i++) {
        if ((name[i] >= 'a' && name[i] <= 'z') ||
            (name[i] >= 'A' && name[i] <= 'Z') ||
            (name[i] >= '0' && name[i] <= '9') || name[i] == '_')
            continue;
        return 0;
    }
    return 1;
}

static int add(char ***res, char *tmp, int *len)
{
    *res = realloc(*res, sizeof(char *) * (*len + 2));
    if (*res == NULL)
        return ALT_EXIT;
    (*res)[*len] = my_strdup(tmp);
    (*res)[*len + 1] = NULL;
    if ((*res)[*len] == NULL)
        return ALT_EXIT;
    *len += 1;
    return SUCCESS_EXIT;
}

static char **take_action_end(char *tmp, const char *end,
    bool *error, char **res)
{
    if (tmp && my_strcmp(tmp, end) == 0) {
        free(tmp);
        return res;
    }
    *error = true;
    free(tmp);
    free_array(res);
    return NULL;
}

char **take_action(bool *error, const char *end)
{
    char **res = malloc(sizeof(char *));
    char *tmp = NULL;
    size_t len_w = 0;
    int len = 0;

    if (res == NULL)
        return NULL;
    res[0] = NULL;
    while (getline(&tmp, &len_w, stdin) != -1) {
        tmp[my_strlen(tmp) - 1] = '\0';
        if (my_strcmp(tmp, end) == 0)
            break;
        if (add(&res, tmp, &len) == ALT_EXIT) {
            free(tmp);
            free_array(res);
            return NULL;
        }
    }
    return take_action_end(tmp, end, error, res);
}

int from_one_line(tcsh_t *term, char *cmd)
{
    char *repeat_cmd = NULL;

    if (strncmp(cmd, "repeat ", 7) == 0 || strncmp(cmd, "repeat", 6) == 0) {
        term->nb_nb_repeat = 0;
        check_repeat(cmd, term);
        if (check_error(term, cmd, atoi(term->return_value)) == FAILURE_EXIT)
            return ALT_EXIT;
        repeat_cmd = cut_len(cmd, 7 + term->nb_nb_repeat);
        free(cmd);
        cmd = repeat_cmd;
        if (cmd == NULL)
            return ALT_EXIT;
    }
    return repeat_or_no_repeat(term, cmd, atoi(term->return_value));
}

static int update_depth(char *line, int depth)
{
    if (strncmp(line, "if ", 3) == 0)
        return depth + 1;
    if (my_strcmp(line, "endif") != 0)
        return depth;
    if (depth > 0)
        return depth - 1;
    return -1;
}

static int find_if_end(char **action, int start)
{
    int depth = 0;

    for (int j = start + 1; action[j] != NULL; j++) {
        depth = update_depth(action[j], depth);
        if (depth == -1)
            return j;
    }
    return -1;
}

static void feed_if_pipe(int fd, char **action, int from, int to)
{
    for (int k = from; k <= to; k++) {
        write(fd, action[k], my_strlen(action[k]));
        write(fd, "\n", 1);
    }
}

static int run_if_block(tcsh_t *term, char **action, int *i)
{
    int j = find_if_end(action, *i);
    int in[2] = {-1, -1};
    int save_in = dup(STDIN_FILENO);
    int res = ALT_EXIT;

    if (j == -1)
        return my_cmd_error(": then/endif not found.\n", "then", ALT_EXIT);
    if (pipe(in) == -1 || save_in == -1)
        return ALT_EXIT;
    feed_if_pipe(in[1], action, *i + 1, j);
    close(in[1]);
    dup2(in[0], STDIN_FILENO);
    close(in[0]);
    res = from_one_line(term, my_strdup(action[*i]));
    dup2(save_in, STDIN_FILENO);
    close(save_in);
    *i = j;
    return res;
}

int foreach_execute_actions(tcsh_t *term, char **action)
{
    char **tmp = NULL;
    int res = SUCCESS_EXIT;

    for (int i = 0; action[i] != NULL; i++) {
        tmp = my_str_to_word_array(action[i], " \t\n");
        if (tmp != NULL && tmp[0] != NULL && my_strcmp(tmp[0], "if") == 0)
            res = run_if_block(term, action, &i);
        else
            res = from_one_line(term, my_strdup(action[i]));
        free_array(tmp);
        if (res != SUCCESS_EXIT)
            return res;
    }
    return SUCCESS_EXIT;
}
