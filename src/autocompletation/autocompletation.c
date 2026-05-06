/*
** EPITECH PROJECT, 2026
** 42sh
** File description:
** autocompletation
*/

#include "../../include/struct.h"
#include <glob.h>

static void write_argument(char **cmd, tcsh_t *term)
{
    char *lign = fill_buff("/etc/hostname");
    char *user = take_value(term->env, "USERNAME");
    int tmp = 0;

    if (lign) {
        my_strip_newline(lign);
        write(1, lign, my_strlen(lign));
    }
    write(1, ":", 1);
    free(lign);
    lign = take_value(term->env, "PWD");
    if (lign && user) {
        tmp = my_strn(lign, user);
        if (tmp != 0)
            write(1, "~", 1);
        write(1, lign + tmp, my_strlen(lign + tmp));
    }
    write(1, "> ", 2);
}

static char **dup_array(char **arr, glob_t *globstruct)
{
    int len = len_array(arr);
    char **new = NULL;

    if (len > 0)
        new = malloc(sizeof(char *) * (len + 1));
    if (!new) {
        globfree(globstruct);
        return new;
    }
    for (int i = 0; i < len; i++) {
        new[i] = my_strdup(arr[i]);
    }
    new[len] = NULL;
    globfree(globstruct);
    return new;
}

static char **add(char *partial_cmd, char **tmp_char, int i, char **tab)
{
    glob_t results;
    char pattern[256];
    char **new_tab = NULL;

    if (chdir(tmp_char[i]) == 84)
        return tab;
    snprintf(pattern, sizeof(pattern), "%s*", partial_cmd);
    if (glob(pattern, GLOB_NOSORT, NULL, &results) == 0) {
        new_tab = dup_array(results.gl_pathv, &results);
        if (new_tab) {
            free_array(tab);
            tab = new_tab;
        }
    }
    return tab;
}

char **other_commande(char **tab, tcsh_t *term, getline_t *st_g, char *partial_cmd)
{
    nodes_t *tmp = NULL;
    char **tmp_char = NULL;
    char *t = NULL;
    char *path_return = NULL;

    path_return = getcwd(NULL, 0);
    if (path_return == NULL)
        return NULL;
    tmp = search_node(term->env, "PATH");
    t = (char *)tmp->data;
    tmp_char = my_str_to_word_array(t, ":\n=");
    for (int i = 0; tmp_char[i] != NULL; i++)
        tab = add(partial_cmd, tmp_char, i, tab);
    chdir(path_return);
    free(path_return);
    free_array(tmp_char);
    return tab;
}

char **autocomplete_command(char *partial_cmd, tcsh_t *term, getline_t *st_g)
{
    glob_t results;
    char pattern[256];
    char **tab = NULL;

    snprintf(pattern, sizeof(pattern), "%s*", partial_cmd);
    if (glob(pattern, GLOB_NOSORT, NULL, &results) == 0) {
        tab = dup_array(results.gl_pathv, &results);
        show_array(tab);
    } else {
        globfree(&results);
    }
    tab = other_commande(tab, term, st_g, partial_cmd);
    return tab;
}

int autocompletation(tcsh_t *term, getline_t *st_g)
{
    char *cmd = st_g->line;
    char **result = NULL;

    result = autocomplete_command(cmd, term, st_g);
    if (result == NULL)
        return FAILURE_EXIT;
    for (int i = 0; result[i] != NULL; i++) {
        printf("%s\n", result[i]);
    }
    free_array(result);
    write_argument(NULL, term);
    write(1, st_g->line, my_strlen(st_g->line));
    return 0;
}
