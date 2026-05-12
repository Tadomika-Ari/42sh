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
Test(shell, choose_command_repeat_builtin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("repeat 2 echo test_repeat");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_if_syntax_path, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("if ( 1 ) echo ok");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_foreach_syntax_path, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("foreach x ( a b ) echo $x");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_backticks_path, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("echo `echo backticks_ok`");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_glob_path, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("echo src/*");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_out_redirection_simple, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("echo redir_out > /tmp/42sh_ut_out.txt");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_out_redirection_append, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("echo redir_append >> /tmp/42sh_ut_out.txt");

    cr_assert_not_null(term);
    cr_assert_not_null(cmd);
    choose_command(term, cmd);
    free(term);
}

Test(shell, choose_command_in_redirection_simple, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *prep = my_strdup("echo redir_in > /tmp/42sh_ut_in.txt");
    char *cmd = my_strdup("cat < /tmp/42sh_ut_in.txt");

    cr_assert_not_null(term);
    cr_assert_not_null(prep);
    cr_assert_not_null(cmd);
    choose_command(term, prep);
    choose_command(term, cmd);
    free(term);
}

Test(shell, parser3000_with_backticks_tokens, .init = redirect_all_std)
{
    char **tab = parser3000("echo `echo parser_ok`", "\t \n");

    cr_assert_not_null(tab);
    cr_assert(len_array(tab) >= 1);
    free_array(tab);
}

Test(shell, parser3000_with_glob_tokens, .init = redirect_all_std)
{
    char **tab = parser3000("echo src/*.c", "\t \n");

    cr_assert_not_null(tab);
    cr_assert(len_array(tab) >= 1);
    free_array(tab);
}

Test(shell, cut_len_basic, .init = redirect_all_std)
{
    char *str = cut_len("Hello World", 6);

    cr_assert_str_eq(str, "World");
    free(str);
}

Test(shell, cut_len_null, .init = redirect_all_std)
{
    char *str = cut_len("Hello", 10);

    cr_assert_null(str);
    free(str);
}

Test(shell, my_lenbase, .init = redirect_all_std)
{
    int nb = my_lenbase(100, 10);

    cr_assert_eq(nb, 3);
}

Test(shell, my_lenbase_negative, .init = redirect_all_std)
{
    int nb = my_lenbase(-42, 10);

    cr_assert_eq(nb, 3);
}

Test(shell, reapet_error_only_spaces, .init = redirect_all_std)
{
    int nb = is_only_spaces("            ");

    cr_assert_eq(nb, 1);
}

Test(shell, reapet_error_char, .init = redirect_all_std)
{
    int nb = is_only_spaces("    y");

    cr_assert_eq(nb, 0);
}

Test(shell, reapet_error_null, .init = redirect_all_std)
{
    int nb = is_only_spaces(NULL);

    cr_assert_eq(nb, 1);
}

Test(shell, repeat_error_check_error, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("rp");
    int nb = check_error(term, cmd, 0);

    cr_assert_eq(nb, FAILURE_EXIT);
    free(term);
}

Test(shell, fail_check_error, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("test");
    int nb = check_error(term, cmd, 0);

    cr_assert_eq(nb, FAILURE_EXIT);
    free(term);
}

Test(shell, repeat_error_fail_check_one, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("test");
    int nb = fail_repeat_check(term, cmd, 0);

    cr_assert_eq(nb, FAILURE_EXIT);
    free(term);
}

Test(shell, repeat_error_fail_valid, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("test 3 echo three");
    int nb = fail_repeat_check(term, cmd, 0);

    cr_assert_eq(nb, SUCCESS_EXIT);
    free(term);
    free(cmd);
}

Test(shell, check_repeat_av_null, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *av = NULL;
    int nb = check_repeat(av, term);

    cr_assert_eq(nb, FAILURE_EXIT);
    free(term);
}

Test(shell, check_repeat_tmp_one, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    int nb = check_repeat("one", term);

    cr_assert_eq(nb, FAILURE_EXIT);
    free(term);
}

Test(shell, check_repeat_success, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    int nb = check_repeat("repeat 3 echo three", term);

    cr_assert_eq(nb, SUCCESS_EXIT);
    cr_assert_eq(term->nb_repeat, 3);
    cr_assert_eq(term->is_repeat, TRUE);
    free(term);
}

Test(shell, check_repeat_space_cmd, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *cmd = my_strdup("    ");
    int nb = repeat_or_no_repeat(term, cmd, 0);

    cr_assert_eq(nb, 0);
    free(term);
}

Test(shell, my_strip_newline_null, .init = redirect_all_std)
{
    char *str = NULL;
    char *res = my_strip_newline(str);

    cr_assert_null(res);
}

Test(shell, has_newline, .init = redirect_all_std)
{
    char *str = my_strdup("test\n");
    char *res = my_strip_newline(str);

    cr_assert_str_eq(str, "test");
    free(str);
}

Test(shell, fill_buff_no_file, .init = redirect_all_std)
{
    char *res = fill_buff("no_file.txt");

    cr_assert_null(res);
}

Test(shell, fill_buff_file, .init = redirect_all_std)
{
    char *res = fill_buff("Makefile");

    cr_assert_not_null(res);
    free(res);
}

Test(shell, free_jobs, .init = redirect_all_std)
{
    job_t *job = calloc(1, sizeof(job_t));
    job->id = 4;
    job->cmd = my_strdup("test");
    job->next = NULL;
    free_jobs(job);
}

Test(shell, add_job_basic, .init = redirect_all_std)
{
    tcsh_t term = {0};

    add_job(&term, 42, "sleep 5", RUNNING);
    cr_assert_not_null(term.jobs);
    cr_assert_eq(term.jobs->id, 1);
    cr_assert_str_eq(term.jobs->cmd, "sleep 5");
    free_jobs(term.jobs);
}

Test(shell, add_job_multiple, .init = redirect_all_std)
{
    tcsh_t term = {0};

    add_job(&term, 10, "cmd1", RUNNING);
    add_job(&term, 20, "cmd2", STOPPED);
    cr_assert_not_null(find_job_id(&term, 1));
    cr_assert_not_null(find_job_id(&term, 2));
    cr_assert_null(find_job_id(&term, 99));
    free_jobs(term.jobs);
}

Test(shell, find_job_by_pid, .init = redirect_all_std)
{
    tcsh_t term = {0};

    add_job(&term, 777, "myjob", STOPPED);
    cr_assert_not_null(find_job_pid(&term, 777));
    cr_assert_null(find_job_pid(&term, 999));
    free_jobs(term.jobs);
}

Test(shell, find_job_null_term, .init = redirect_all_std)
{
    cr_assert_null(find_job_id(NULL, 1));
    cr_assert_null(find_job_pid(NULL, 1));
}

Test(shell, remove_job_first, .init = redirect_all_std)
{
    tcsh_t term = {0};

    add_job(&term, 1, "a", RUNNING);
    add_job(&term, 2, "b", RUNNING);
    remove_job(&term, term.jobs);
    cr_assert_null(find_job_id(&term, 1));
    cr_assert_not_null(find_job_id(&term, 2));
    free_jobs(term.jobs);
}

Test(shell, remove_job_last, .init = redirect_all_std)
{
    tcsh_t term = {0};
    job_t *last = NULL;

    add_job(&term, 1, "a", RUNNING);
    add_job(&term, 2, "b", RUNNING);
    last = find_job_id(&term, 2);
    remove_job(&term, last);
    cr_assert_null(find_job_id(&term, 2));
    cr_assert_not_null(find_job_id(&term, 1));
    free_jobs(term.jobs);
}

Test(shell, get_max_job_id, .init = redirect_all_std)
{
    tcsh_t term = {0};

    cr_assert_eq(get_max_job_id(&term), 0);
    add_job(&term, 1, "a", RUNNING);
    add_job(&term, 2, "b", RUNNING);
    cr_assert_eq(get_max_job_id(&term), 2);
    free_jobs(term.jobs);
}

Test(shell, print_return_val, .init = redirect_all_std)
{
    job_t job = {0};

    cr_assert_eq(print_return(STDERR_FILENO, "err\n"), ALT_EXIT);
    cr_assert_eq(no_such_job(NULL, "no job\n"), ALT_EXIT);
    cr_assert_eq(no_such_job(&job, "no job\n"), EXIT_SUCCESS);
}

Test(shell, job_control_null_cmd, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));

    cr_assert_eq(job_control(term, NULL), FAILURE_EXIT);
    free(term);
}

Test(shell, job_control_echo, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    cr_assert_eq(job_control(term, my_strdup("echo hi")), SUCCESS_EXIT);
    free_array(env);
    free(term);
}

Test(shell, job_control_and_operator, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    job_control(term, my_strdup("echo a && echo b"));
    free_array(env);
    free(term);
}

Test(shell, job_control_or_operator, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    job_control(term, my_strdup("false_xyz || echo fallback"));
    free_array(env);
    free(term);
}

Test(shell, job_execution_null_args, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));
    jobs_exec_t sta = {0};

    cr_assert_eq(job_execution(term, &sta, NULL, NULL), FALSE);
    free(term);
}

Test(shell, job_execution_and, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    jobs_exec_t sta = {0};
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");
    char *cmds[] = {"echo a", "echo b", NULL};
    char *jobs_arr[] = {"&&", "", NULL};

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    job_execution(term, &sta, cmds, jobs_arr);
    free_array(env);
    free(term);
}

Test(shell, loops_multi_func_single, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    cr_assert_eq(loops_multi_func(term, my_strdup("echo hello"), 0),
        SUCCESS_EXIT);
    free_array(env);
    free(term);
}

Test(shell, loops_multi_func_semicolon, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    loops_multi_func(term, my_strdup("echo a; echo b"), 0);
    free_array(env);
    free(term);
}

Test(shell, empty_cmd_detect, .init = redirect_all_std)
{
    cr_assert_eq(empty_cmd_detect(""), TRUE);
    cr_assert_eq(empty_cmd_detect("   "), TRUE);
    cr_assert_eq(empty_cmd_detect("echo"), FALSE);
    cr_assert_eq(empty_cmd_detect(NULL), TRUE);
}

Test(shell, empty_error_case_no_empty, .init = redirect_all_std)
{
    char *cmds[] = {"echo hi", NULL};
    char *jobs[] = {"", NULL};

    cr_assert_eq(empty_error_case(cmds, jobs), FALSE);
}

Test(shell, my_fg_no_jobs, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));
    char **tab = my_str_to_word_array("fg", "\n \t");

    my_fg(term, &tab[1]);
    free_array(tab);
    free(term);
}

Test(shell, my_fg_invalid_id, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *argv[] = {"notanumber", NULL};

    add_job(&term, 1, "test", STOPPED);
    my_fg(&term, argv);
    free_jobs(term.jobs);
}

Test(shell, my_fg_too_many_args, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *argv[] = {"%1", "%2", NULL};

    add_job(&term, 1, "test", STOPPED);
    my_fg(&term, argv);
    free_jobs(term.jobs);
}

Test(shell, my_fg_job_not_found, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *argv[] = {"%99", NULL};

    add_job(&term, 1, "test", STOPPED);
    my_fg(&term, argv);
    free_jobs(term.jobs);
}

Test(shell, my_bg_no_jobs, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));
    char **tab = my_str_to_word_array("bg", "\n \t");

    my_bg(term, &tab[1]);
    free_array(tab);
    free(term);
}

Test(shell, my_bg_invalid_id, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *argv[] = {"notanumber", NULL};

    add_job(&term, 1, "test", STOPPED);
    my_bg(&term, argv);
    free_jobs(term.jobs);
}

Test(shell, my_bg_too_many_args, .init = redirect_all_std)
{
    tcsh_t term = {0};
    char *argv[] = {"%1", "%2", NULL};

    add_job(&term, 1, "test", STOPPED);
    my_bg(&term, argv);
    free_jobs(term.jobs);
}

Test(shell, my_set_display_empty, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("", " ");

    cr_assert_eq(my_set(term, tab), SUCCESS_EXIT);
    free_array(tab);
    free(term);
}

Test(shell, my_set_with_equals, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"myvar", "=", "42", NULL};

    cr_assert_eq(my_set(term, argv), SUCCESS_EXIT);
    cr_assert_not_null(term->locals);
    free(term);
}

Test(shell, my_set_no_value, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"bare_var", NULL};

    my_set(term, argv);
    cr_assert_not_null(term->locals);
    free(term);
}

Test(shell, my_set_inline_eq, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"x=hello", NULL};

    my_set(term, argv);
    cr_assert_not_null(term->locals);
    free(term);
}

Test(shell, my_set_update_existing, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *a[] = {"x", "=", "old", NULL};
    char *b[] = {"x", "=", "new", NULL};

    my_set(term, a);
    cr_assert_eq(my_set(term, b), SUCCESS_EXIT);
    free(term);
}

Test(shell, my_set_then_free_all, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *a[] = {"x", "=", "1", NULL};
    char *b[] = {"y", "=", "2", NULL};

    my_set(term, a);
    my_set(term, b);
    free_all(term);
}

Test(shell, my_which_too_few_args, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("which", "\n \t");

    cr_assert_eq(my_which(term, &tab[1]), ALT_EXIT);
    free_array(tab);
    free(term);
}

Test(shell, my_which_find_builtin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *envp[] = {"PATH=/usr/bin:/bin", NULL};
    char *argv[] = {"cd", NULL};

    init(term, envp);
    cr_assert_eq(my_which(term, argv), SUCCESS_EXIT);
    free_all(term);
}

Test(shell, my_which_find_binary, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");
    char *argv[] = {"ls", NULL};

    my_setenv(term, env);
    my_which(term, argv);
    free_array(env);
    free(term);
}

Test(shell, my_which_not_found, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"nonexistent_xyz_abc", NULL};

    cr_assert_eq(my_which(term, argv), ALT_EXIT);
    free(term);
}

Test(shell, my_which_aliased, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *alias_cmd[] = {"myls", "ls", NULL};
    char *argv[] = {"myls", NULL};

    my_alias(term, alias_cmd);
    my_which(term, argv);
    free(term);
}

Test(shell, my_where_too_few_args, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("where", "\n \t");

    cr_assert_eq(my_where(term, &tab[1]), ALT_EXIT);
    free_array(tab);
    free(term);
}

Test(shell, my_where_ls, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");
    char *argv[] = {"ls", NULL};

    my_setenv(term, env);
    fill_rc(term);
    my_where(term, argv);
    free_array(env);
    free(term);
}

Test(shell, apply_null_cmd, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));

    cr_assert_eq(apply(term, NULL), ALT_EXIT);
    free(term);
}

Test(shell, execute_cmd_null, .init = redirect_all_std)
{
    tcsh_t *term = malloc(sizeof(tcsh_t));

    cr_assert_eq(execute_cmd(term, NULL), ALT_EXIT);
    free(term);
}

Test(shell, is_then_null, .init = redirect_all_std)
{
    cr_assert_eq(is_then(NULL), 0);
}

Test(shell, is_then_no_then, .init = redirect_all_std)
{
    char *argv[] = {"echo", "hi", NULL};

    cr_assert_eq(is_then(argv), 0);
}

Test(shell, is_then_at_end, .init = redirect_all_std)
{
    char *argv[] = {"1", "then", NULL};

    cr_assert_eq(is_then(argv), 1);
}

Test(shell, is_then_not_last, .init = redirect_all_std)
{
    char *argv[] = {"then", "echo", NULL};

    cr_assert_eq(is_then(argv), -1);
}

Test(shell, dupl_array_basic, .init = redirect_all_std)
{
    char *src[] = {"a", "b", "c", NULL};
    char **copy = dupl_array(src);

    cr_assert_not_null(copy);
    cr_assert_str_eq(copy[0], "a");
    cr_assert_null(copy[3]);
    free_array(copy);
}

Test(shell, my_if_no_args, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("if", "\n \t");

    my_if(term, &tab[1]);
    free_array(tab);
    free(term);
}

Test(shell, my_if_false_no_then, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"0", "echo", "skip", NULL};

    term->return_value = my_strdup("0");
    cr_assert_eq(my_if(term, argv), SUCCESS_EXIT);
    free(term);
}

Test(shell, my_if_true_no_then, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");
    char *argv[] = {"1", "echo", "run", NULL};

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    my_if(term, argv);
    free_array(env);
    free(term);
}

Test(shell, my_if_empty_condition, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"1", NULL};

    term->return_value = my_strdup("0");
    my_if(term, argv);
    free(term);
}

Test(shell, foreach_is_valid_name_valid, .init = redirect_all_std)
{
    cr_assert_eq(foreach_is_valid_name("x"), 1);
    cr_assert_eq(foreach_is_valid_name("_var"), 1);
    cr_assert_eq(foreach_is_valid_name("Var123"), 1);
}

Test(shell, foreach_is_valid_name_invalid, .init = redirect_all_std)
{
    cr_assert_eq(foreach_is_valid_name("1bad"), 0);
    cr_assert_eq(foreach_is_valid_name("my-var"), 0);
    cr_assert_eq(foreach_is_valid_name(""), 0);
    cr_assert_eq(foreach_is_valid_name(NULL), 0);
}

Test(shell, my_foreach_too_few_args, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **tab = my_str_to_word_array("foreach", "\n \t");

    cr_assert_eq(my_foreach(term, &tab[1]), ALT_EXIT);
    free_array(tab);
    free(term);
}

Test(shell, my_foreach_too_many_args, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"x", "(a b)", "extra", NULL};

    cr_assert_eq(my_foreach(term, argv), ALT_EXIT);
    free(term);
}

Test(shell, my_foreach_invalid_varname, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char *argv[] = {"1bad", "(a b)", NULL};

    cr_assert_eq(my_foreach(term, argv), ALT_EXIT);
    free(term);
}

Test(shell, foreach_via_piped_stdin, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");
    int pipefd[2];
    int saved_stdin = 0;
    char *argv[] = {"x", "(a b c)", NULL};

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    cr_assert_eq(pipe(pipefd), 0);
    write(pipefd[1], "echo $x\nend\n", 12);
    close(pipefd[1]);
    saved_stdin = dup(STDIN_FILENO);
    dup2(pipefd[0], STDIN_FILENO);
    close(pipefd[0]);
    my_foreach(term, argv);
    dup2(saved_stdin, STDIN_FILENO);
    close(saved_stdin);
    free_array(env);
    free(term);
}

Test(shell, from_one_line_echo, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PATH=/usr/bin:/bin", " ");

    my_setenv(term, env);
    term->return_value = my_strdup("0");
    cr_assert_eq(from_one_line(term, my_strdup("echo test")), SUCCESS_EXIT);
    free_array(env);
    free(term);
}

Test(shell, simple_char, .init = redirect_all_std)
{
    char *s = simple('Z');

    cr_assert_not_null(s);
    cr_assert_str_eq(s, "Z");
    free(s);
}

Test(shell, array_null_basic, .init = redirect_all_std)
{
    char **arr = array_null('x');

    cr_assert_not_null(arr);
    cr_assert_str_eq(arr[0], "x");
    free_array(arr);
}

Test(shell, my_str_rea_concat, .init = redirect_all_std)
{
    char *base = my_strdup("hello");

    base = my_str_rea(base, " world");
    cr_assert_str_eq(base, "hello world");
    free(base);
}

Test(shell, my_str_rea_null_value, .init = redirect_all_std)
{
    char *base = my_strdup("hello");

    base = my_str_rea(base, NULL);
    cr_assert_str_eq(base, "hello");
    free(base);
}

Test(shell, without_braces, .init = redirect_all_std)
{
    char *s = without("{myvar}");

    cr_assert_str_eq(s, "myvar");
    free(s);
}

Test(shell, get_name_basic, .init = redirect_all_std)
{
    char *name = get_name("hello", 4);

    cr_assert_str_eq(name, "hello");
    free(name);
}

Test(shell, sweeper_dollar_home, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    bool error = false;
    char *set_home[] = {"HOME", "/tmp", NULL};
    char **res = NULL;

    my_setenv(term, set_home);
    res = sweeper(term, "echo $HOME", &error);
    cr_assert_not_null(res);
    free_array(res);
    free(term);
}

Test(shell, sweeper_dollar_cwd, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    bool error = false;
    char **res = sweeper(term, "echo $cwd", &error);

    cr_assert_not_null(res);
    free_array(res);
    free(term);
}

Test(shell, sweeper_dollar_undefined, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    bool error = false;

    sweeper(term, "echo $UNDEFINED_VAR_XYZ", &error);
    free(term);
}

Test(shell, my_cd_to_tmp, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("/tmp", "\n \t");
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PWD=/home", " ");

    my_setenv(term, env);
    cr_assert_eq(my_cd(term, tab), SUCCESS_EXIT);
    free_array(tab);
    free_array(env);
    free(term);
}

Test(shell, my_cd_back_with_dash, .init = redirect_all_std)
{
    tcsh_t *term = calloc(1, sizeof(tcsh_t));
    char **env = my_str_to_word_array("PWD=/home", " ");
    char *argv_tmp[] = {"/tmp", NULL};
    char *argv_dash[] = {"-", NULL};

    my_setenv(term, env);
    my_cd(term, argv_tmp);
    cr_assert_eq(my_cd(term, argv_dash), SUCCESS_EXIT);
    free_array(env);
    free(term);
}

Test(shell, my_cd_file_not_dir, .init = redirect_all_std)
{
    char **tab = my_str_to_word_array("/bin/ls", "\n \t");
    tcsh_t *term = malloc(sizeof(tcsh_t));

    my_cd(term, tab);
    free_array(tab);
    free(term);
}
