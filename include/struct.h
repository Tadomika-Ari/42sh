/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** struct
*/

#ifndef MY_TOP_STRUCT_H
    #define MY_TOP_STRUCT_H
    #include "my.h"

typedef enum exit
{
    SUCCESS_EXIT = 0,
    ALTERNATIVE_EXIT = 1,
    TRUE = 1,
    FALSE = 0,
    LIFE = 42,
    DEAD = -1,
    FAILURE_EXIT = 84,
}exit_t;

typedef struct history
{
    char *cmd;
    char *time;
    int index;
}history_t;


typedef struct tcsh {
    nodes_t *env;
    nodes_t *func;
    int life;
    char *old;
    int fd[2];
    int pipe_fd[2];
    bool first;
    bool last;
    int prev;
    nodes_t *history;
    int len_history;
} tcsh_t;

typedef struct function {
    const char *name;
    int (*cmd)(tcsh_t *, char **);
} function_t;

int init(tcsh_t *term, char **env);

int error_alphanumeric(char *cmd);

int error_not_enough_argument(char *cmd);

int error_too_many_argument(char *cmd);

int error_permission_denied(char *cmd);

int error_first_caracter(char *cmd);

int error_no_home(char *cmd);

int command_not_found(char *cmd);

int path_not_found(char *path);

int error_syntax(char *cmd);

int env(tcsh_t *term, char **argv);

int my_cd(tcsh_t *term, char **argv);

void algo_exit(int *result);

int error_expression_syntax(char *cmd);

nodes_t *create_new_node(char *lign_env);

int my_exit(tcsh_t *term, char **argv);

char *take_value(nodes_t *head, char *cat);

int my_setenv(tcsh_t *term, char **argv);

int correct_type(char **cmd);

int reinit(tcsh_t *term, char *cmd, char **cmd_pipe);

int my_unsetenv(tcsh_t *term, char **argv);

int user_entry(tcsh_t *term, char **cmd);

int my_sh(char **env);

int exec(char *bin, char **command, tcsh_t *term, char *cmd);

void free_all(tcsh_t *term);

int choose_command(tcsh_t *term, char *cmd);

int is_it_file(char *path);

int error_not_a_directory(char *cmd);

int error_ambigious(void);

char *crop(char *argv);

int search_ind(char *argv, char c);

int search_out(char *argv);

int search_in(char *argv);

int error_null(void);

int correct_lign(char *cmd, char **cmd_pipe);

int my_free(void **pointer, int max, int exit);

int argument_not_support(char *cmd);

int my_history(tcsh_t *term, char **cmd);

int push_to_history(tcsh_t *term, char *cmd);

int my_getline(char **cmd, size_t *len);

#endif
