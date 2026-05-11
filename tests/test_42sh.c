/*
** EPITECH PROJECT, 2026
** unit
** File description:
** test
*/

#include <criterion/criterion.h>
#include <criterion/redirect.h>
#include "../include/struct.h"

static nodes_t *make_alias_node(const char *name, const char *cmd)
{
    nodes_t *node = malloc(sizeof(nodes_t));
    alias_t *alias = malloc(sizeof(alias_t));

    if (node == NULL || alias == NULL) {
        free(node);
        free(alias);
        return NULL;
    }
    alias->name_alias = my_strdup(name);
    alias->cmd_alias = my_strdup(cmd);
    if (alias->name_alias == NULL || alias->cmd_alias == NULL) {
        free(alias->name_alias);
        free(alias->cmd_alias);
        free(alias);
        free(node);
        return NULL;
    }
    node->data = alias;
    node->next = NULL;
    return node;
}

static void free_alias_nodes_list(nodes_t *head)
{
    nodes_t *next = NULL;
    alias_t *alias = NULL;

    for (nodes_t *cur = head; cur != NULL; cur = next) {
        next = cur->next;
        alias = cur->data;
        if (alias != NULL) {
            free(alias->name_alias);
            free(alias->cmd_alias);
            free(alias);
        }
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

Test(shell, my_alias, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("toto", " \n\t");

    my_alias(term, tab);
    free_array(tab);
}

Test(shell, my_alias_print, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("toto", " \n\t");

    my_alias(term, &tab[1]);
    free_array(tab);
}

Test(shell, my_alias_print_add, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("toto tata", " \n\t");

    my_alias(term, tab);
    my_alias(term, &tab[2]);
    free_array(tab);
}

Test(shell, my_alias_unique_alias, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("toto tata", " \n\t");

    my_alias(term, tab);
    my_alias(term, &tab[1]);
    free_array(tab);
}
Test(shell, my_alias_change_alias, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("toto tata", " \n\t");

    my_alias(term, tab);
    my_alias(term, &tab[1]);
    tab[1][0] = 'u';
    my_alias(term, tab);
    free_array(tab);
}


Test(shell, my_alias_and_check_alias, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *alias = NULL;
    char *cmd[] = {"tata", "echo", "Test Marche bien", NULL};

    cr_assert_eq(my_alias(&term, cmd), SUCCESS_EXIT);
    alias = check_alias(&term, "tata");
    cr_assert_not_null(alias);
    free(alias);
    free_alias_nodes_list(term.alias);
}

Test(shell, check_alias_not_found, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *alias = NULL;

    term.alias = make_alias_node("tata", "echo ok");
    cr_assert_not_null(term.alias);
    alias = check_alias(&term, "toto");
    cr_assert_null(alias);
    free_alias_nodes_list(term.alias);
}

Test(shell, push_to_history, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));

    push_to_history(term, "jungle diff");
}

Test(shell, dangerous_alias_keyword, .init = redirect_all_std)
{
    char *cmd[] = {"alias", "something", NULL};

    int ret = my_alias(NULL, cmd);
    cr_assert_eq(ret, ALT_EXIT);
    cr_assert_stdout_eq_str("alias: Too dangerous to alias that.\n");
}


Test(shell, alias_loop_detection, .init = redirect_all_std)
{
    tcsh_t term = {0};
    nodes_t *first = NULL;
    nodes_t *second = NULL;
    char *res = NULL;

    first = make_alias_node("a", "bonjour");
    second = make_alias_node("bonjour", "a");
    cr_assert_not_null(first);
    cr_assert_not_null(second);
    first->next = second;
    term.alias = first;
    res = alias(&term, my_strdup("a"));
    cr_assert_null(res);
    cr_assert_stderr_eq_str("Alias loop.\n");
    free_alias_nodes_list(term.alias);
}

Test(shell, alias_test_alias_and_check, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *cmd[] = {"test_alias", "alias_OK", NULL};
    char *alias = NULL;

    cr_assert_eq(my_alias(&term, cmd), SUCCESS_EXIT);
    alias = check_alias(&term, "test_alias");
    cr_assert_not_null(alias);
    cr_assert_str_eq(alias, "alias_OK");
    free(alias);
    free_alias_nodes_list(term.alias);
}

Test(shell, alias_test_ls_and_check, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *cmd[] = {"test_ls", "ls", "-l", NULL};
    char *alias = NULL;

    cr_assert_eq(my_alias(&term, cmd), SUCCESS_EXIT);
    alias = check_alias(&term, "test_ls");
    cr_assert_not_null(alias);
    cr_assert_str_eq(alias, "ls -l");
    free(alias);
    free_alias_nodes_list(term.alias);
}


Test(shell, strip_single_quotess, .init = redirect_all_std)
{
    char *str = my_strdup("\'toto\'");
    char *res = strip_single_quotes(str);

    free(str);
    free(res);
}

Test(shell, strip_single_quotes_to_short, .init = redirect_all_std)
{
    char *str = my_strdup("a");
    char *res = strip_single_quotes(str);

    free(str);
    free(res);
}

Test(shell, strip_single_quotess_null, .init = redirect_all_std)
{
    char *res = strip_single_quotes(NULL);
}

Test(shell, check_aliam_linked_list_empty, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *str = my_strdup("ceci est un test que qualité qualitatif");
    check_alias(&term, str);
}

Test(shell, choose_command_where_builtin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("where ls");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    fill_rc(term);
    choose_command(term, cmd);
    free(term);
}
Test(shell, choose_command_which_builtin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("which ls");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    fill_rc(term);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_set_builtin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("set");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_bg_builtin_no_job, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("bg");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_fg_builtin_no_job, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("fg");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

