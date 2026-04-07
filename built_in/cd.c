/*
** EPITECH PROJECT, 2026
** minishell1
** File description:
** cd
*/

#include "../include/struct.h"

int new_path(tcsh_t *term, char *old)
{
    char *pwd = NULL;

    pwd = getcwd(pwd, 0);
    if (!pwd)
        return my_free((void *[]){old}, 1, FAILURE_EXIT);
    if (my_strcmp(pwd, old) != 0) {
        if (term->old)
            free(term->old);
        term->old = my_strdup(old);
    }
    if (my_setenv(term, (char *[]){"PWD", pwd, NULL}) == FAILURE_EXIT)
        return my_free((void *[]){pwd, old}, 2, FAILURE_EXIT);
    return my_free((void *[]){pwd, old}, 2, SUCCESS_EXIT);
}

int to_path(char **argv, tcsh_t *term, char *pwd)
{
    int exit = chdir(argv[0]);

    if (exit != 0) {
        free(pwd);
        if (errno == EACCES)
            return error_permission_denied(argv[0]);
        if (is_it_file(argv[0]) == 0)
            return error_not_a_directory(argv[0]);
        return path_not_found(argv[0]);
    }
    if (new_path(term, pwd) == FAILURE_EXIT)
        return FAILURE_EXIT;
    return SUCCESS_EXIT;
}

int whitout_argument(tcsh_t *term, char **argv)
{
    char *home = take_value(term->env, "HOME");

    if (!home)
        return error_no_home("cd");
    return my_cd(term, (char *[]){home, NULL});
}

int my_cd(tcsh_t *term, char **argv)
{
    int len = len_array(argv);
    char *pwd = NULL;

    if (len >= 2)
        return error_too_many_argument("cd");
    if (len == 0)
        return whitout_argument(term, argv);
    if (argv[0][0] == '-' && argv[0][1] == '\0') {
        if (!term->old)
            return path_not_found("");
        return my_cd(term, (char *[]){term->old, NULL});
    }
    errno = 0;
    pwd = getcwd(pwd, 0);
    return to_path(argv, term, pwd);
}
