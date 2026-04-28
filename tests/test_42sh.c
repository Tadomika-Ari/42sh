/*
** EPITECH PROJECT, 2026
** unit
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/struct.h"
char *get_rc_file(tcsh_t *term);

static void free_nodes_list(nodes_t *head)
{
    nodes_t *next = NULL;

    for (nodes_t *cur = head; cur != NULL; cur = next) {
        next = cur->next;
        free(cur->data);
        free(cur);
    }
}

void redirect_all_std(void)
{
    cr_redirect_stdout();
    cr_redirect_stderr();
}

Test(shell, parser_test, .init = redirect_all_std)
{
    char **tab = parser3000("echo 'ceci est un test'", "\t \n");

    cr_assert(len_array(tab) == 2);
    free_array(tab);
}

Test(shell, init_shell, .init = redirect_all_std)
{
    init(NULL, NULL);
}

Test(shell, fill_rc, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    fill_rc(term);
    free(term);
}

Test(shell, error_alphanumeric, .init = redirect_all_std)
{
    error_alphanumeric("CMD");
}

Test(shell, error_not_enough_argument, .init = redirect_all_std)
{
    error_not_enough_argument("CMD");
}

Test(shell, error_too_many_argument, .init = redirect_all_std)
{
    error_too_many_argument("CMD");
}

Test(shell, error_permission_denied, .init = redirect_all_std)
{
    error_permission_denied("CMD");
}

Test(shell, error_first_caracter, .init = redirect_all_std)
{
    error_first_caracter("CMD");
}

Test(shell, error_no_home, .init = redirect_all_std)
{
    error_no_home("CMD");
}

Test(shell, command_not_found, .init = redirect_all_std)
{
    command_not_found("CMD");
}

Test(shell, path_not_found, .init = redirect_all_std)
{
    path_not_found("CMD");
}

Test(shell, error_syntax, .init = redirect_all_std)
{
    error_syntax("CMD");
}

Test(shell, error_expression_syntax, .init = redirect_all_std)
{
    error_expression_syntax("CMD");
}

Test(shell, env, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("env", "\n \t");
    tcsh_t *term = malloc(sizeof(tcsh_t));

    env(term, tab);
    free_array(tab);
    free(term);
}

Test(shell, my_cd, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("cd", "\n \t");
    tcsh_t *term = malloc(sizeof(tcsh_t));

    my_cd(term, tab);
    free_array(tab);
    free(term);
}

Test(shell, algo_exit, .init = redirect_all_std)
{
    int exit = 5;
    algo_exit(&exit);
}

Test(shell, my_exit, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("exit", "\n \t");
    tcsh_t *term = malloc(sizeof(tcsh_t));

    my_exit(term, tab);
    free_array(tab);
    free(term);
}

Test(shell, my_setenv, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("setenv toto", "\n \t");
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    my_setenv(term, tab);
    free_array(tab);
    free(term);
}

Test(shell, create_new_node, .init = redirect_all_std)
{
    create_new_node("chocolatine est une vienoiserie");
}

Test(shell, take_value, .init = redirect_all_std)
{
    take_value(NULL, "chocolatine est une vienoiserie");
}

Test(shell, correct_type, .init = redirect_all_std)
{
    correct_type(NULL);
}

Test(shell, correct_type_not_null, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array(
        "jojo's bizarre adventure meilleurs animé pas de débat", " ");

    correct_type(NULL);
    free_array(tab);
}

Test(shell, reinit, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));
    char **tab = my_str_to_word_array(
        "je ne sais pas ce qu'est ce | parametre", "|");

    reinit(term, "kirby triple deluxe", tab);
    free(term);
    free_array(tab);
}

Test(shell, my_unsetenv, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("setenv toto", "\n \t");
    char **tab2 = my_str_to_word_array("unsetenv toto", "\n \t");
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    my_setenv(term, tab);
    my_unsetenv(term, tab2);
    free_array(tab);
    free_array(tab2);
    free(term);
}

Test(shell, error_ambigious, .init = redirect_all_std)
{
    error_ambigious();
}

Test(shell, error_not_a_directory, .init = redirect_all_std)
{
    error_not_a_directory("THIS IS A BUCKET");
}

Test(shell, is_it_file, .init = redirect_all_std)
{
    is_it_file("THIS IS A BUCKET");
}

Test(shell, crop, .init = redirect_all_std)
{
    crop("THIS IS A BUCKET");
}

Test(shell, choose_command, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("pelophlyax kl esculentus | 2 147 483 648");

    choose_command(term, cmd);
    free(term);
}

Test(shell, search_ind, .init = redirect_all_std)
{
    search_ind("tahm kench", 'c');
}

Test(shell, search_out, .init = redirect_all_std)
{
    search_out("cat < ls");
}

Test(shell, search_in, .init = redirect_all_std)
{
    search_in("cat < ls");
}

Test(shell, error_null, .init = redirect_all_std)
{
    error_null();
}

Test(shell, correct_lign, .init = redirect_all_std)
{
    char *cmd = my_strdup("toto | tata");
    char **tab = my_str_to_word_array(cmd, "|");

    correct_lign(cmd, tab);
    free(cmd);
    free_array(tab);
}

Test(shell, my_free, .init = redirect_all_std)
{
    my_free(NULL, 0, 84);
}

Test(shell, argument_not_support, .init = redirect_all_std)
{
    argument_not_support("la lib lapin n'est plus disponible");
}

Test(shell, my_history, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("history", "\t \n");

    my_history(term, tab);
    free_array(tab);
}

Test(shell, my_alias_and_check_alias, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char path[] = "/tmp/42sh_alias_testXXXXXX";
    char *alias = NULL;
    char *content = NULL;
    char *cmd[] = {"tata", "echo", "Test Marche bien", NULL};
    int fd = mkstemp(path);

    cr_assert(fd >= 0);
    term.fd_rc = fd;
    cr_assert_eq(my_alias(&term, cmd), SUCCESS_EXIT);
    lseek(fd, 0, SEEK_SET);
    content = get_rc_file(&term);
    cr_assert_not_null(content);
    cr_assert_str_eq(content, "alias tata='echo Test Marche bien'\n");
    free(content);
    alias = check_alias(&term, "tata");
    cr_assert_not_null(alias);
    cr_assert_str_eq(alias, "echo Test Marche bien");
    free(alias);
    close(fd);
    unlink(path);
}

Test(shell, check_alias_not_found, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char path[] = "/tmp/42sh_alias_testXXXXXX";
    char *alias = NULL;
    int fd = mkstemp(path);

    cr_assert(fd >= 0);
    term.fd_rc = fd;
    write(fd, "alias tata='echo ok'\n", 21);
    alias = check_alias(&term, "toto");
    cr_assert_null(alias);
    close(fd);
    unlink(path);
}

Test(shell, sepecial_variable_cwd, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char cmd[] = "$cwd";
    int ret = 0;

    push_back(&term.env, create_new_node("PWD=/tmp"));
    ret = sepecial_variable(&term, cmd);
    cr_assert_eq(ret, SUCCESS_EXIT);
    cr_assert_stdout_eq_str("/tmp\n");
    free_nodes_list(term.env);
}

Test(shell, sepecial_variable_unknown, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char cmd[] = "$idontexist";
    int ret = 0;

    push_back(&term.env, create_new_node("PWD=/tmp"));
    ret = sepecial_variable(&term, cmd);
    cr_assert_eq(ret, -1);
    cr_assert_stdout_eq_str("");
    free_nodes_list(term.env);
}

Test(shell, push_to_history, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    push_to_history(term, "jungle diff");
}
