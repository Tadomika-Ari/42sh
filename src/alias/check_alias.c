/*
** EPITECH PROJECT, 2026
** check_alias
** File description:
** check_alias
*/

#include "../../include/struct.h"

char *strip_single_quotes(char *word)
{
    int len = 0;
    char *result = NULL;

    if (word == NULL)
        return NULL;
    len = my_strlen(word);
    if (len >= 2 && word[0] == '\'' && word[len - 1] == '\'') {
        result = malloc(len - 1);
        if (result == NULL)
            return NULL;
        for (int i = 1; i < len - 1; i++)
            result[i - 1] = word[i];
        result[len - 2] = '\0';
        return result;
    }
    return my_strdup(word);
}

char *get_rc_file(tcsh_t *term)
{
    struct stat sb;
    char *buf = NULL;
    ssize_t rd = 0;

    if (term->fd_rc == FAILURE_EXIT)
        return NULL;
    if (lseek(term->fd_rc, 0, SEEK_SET) == FAILURE_EXIT)
        return NULL;
    if (fstat(term->fd_rc, &sb) == FAILURE_EXIT)
        return NULL;
    buf = malloc(sb.st_size + 1);
    if (buf == NULL)
        return NULL;
    rd = read(term->fd_rc, buf, sb.st_size);
    if (rd < 0) {
        free(buf);
        return NULL;
    }
    buf[rd] = '\0';
    return buf;
}

char *check_alias(tcsh_t *term, char *cmd)
{
    char *buf = get_rc_file(term);
    char **tab = NULL;
    char *alias = NULL;

    if (buf == NULL)
        return NULL;
    tab = parser3000(buf, "# =\n");
    if (tab == NULL) {
        free(buf);
        return NULL;
    }
    for (int i = 0; tab[i] != NULL && tab[i + 1] != NULL && tab[i + 2] != NULL
        ; i += 3)
        if (my_strcmp(tab[i], "alias") == 0 && my_strcmp(tab[i + 1], cmd) == 0)
            alias = strip_single_quotes(tab[i + 2]);
    free_array(tab);
    free(buf);
    return alias;
}

char *add_rest_to_alias(char *cmd, int i, char *alias)
{
    char *rest = NULL;
    char *result = NULL;

    if (cmd[i] == '\0')
        return alias;
    rest = cmd + i;
    result = malloc(my_strlen(alias) + my_strlen(rest) + 1);
    if (result == NULL)
        return alias;
    result[0] = '\0';
    my_strcat(result, alias);
    my_strcat(result, rest);
    free(cmd);
    free(alias);
    return result;
}

static char *expand_first_word_alias(tcsh_t *term, char *cmd)
{
    char *first_word = NULL;
    char *alias = NULL;
    int i = 0;

    if (cmd == NULL)
        return NULL;
    while (cmd[i] && cmd[i] != ' ' && cmd[i] != '\t')
        i++;
    first_word = malloc(i + 1);
    if (first_word == NULL)
        return cmd;
    for (int j = 0; j < i; j++)
        first_word[j] = cmd[j];
    first_word[i] = '\0';
    alias = check_alias(term, first_word);
    free(first_word);
    if (alias == NULL)
        return cmd;
    return add_rest_to_alias(cmd, i, alias);
}

char *alias(tcsh_t *term, char *cmd)
{
    char *new_expanded = NULL;
    char *expanded = cmd;

    while (1) {
        new_expanded = expand_first_word_alias(term, expanded);
        if (new_expanded == expanded)
            break;
        expanded = new_expanded;
    }
    return expanded;
}
