/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** struct
*/

#ifndef MY_TOP_STRUCT_H
    #define MY_TOP_STRUCT_H
    #include "my.h"
    #include <termios.h>
    #define INITIAL_CAPACITY 128
    #define MAX_LINE 1024


    #define RC_FILE ".42rc"

    #define UNMATCH_SINGLE "Unmatched '''.\n"

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

typedef struct getline
{
    struct termios old_t;
    struct termios raw_t;
    size_t cap;
    size_t line_len;
    char *line;
    char c;
    ssize_t rd;
    int statut_getline;
    int statut_exit_getline;
    int statut_echo;
    int statut_history;
}getline_t;

typedef enum job_state {
    RUNNING,
    STOPPED,
    DONE
} job_state_t;

typedef struct job {
    int id;
    pid_t pgid;
    char *cmd;
    job_state_t state;
    struct job *next;
} job_t;

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
    int fd_rc;
    int check_history;
    int whereiscursor;
    int maxposcursor;
    job_t *jobs;
    pid_t shell_pgid;
    struct termios shell_tmodes;
    pid_t fg_pgid;
    bool is_background;  // Ajoutez cette ligne
} tcsh_t;

typedef struct function {
    const char *name;
    int (*cmd)(tcsh_t *, char **);
} function_t;

typedef struct parse {
    int in_quote;
    int in_tick;
    int parent;
    int brack;
    int count;
    int start;
    int i;
} parse_t;

int init(tcsh_t *term, char **env);

int fill_rc(tcsh_t *term);

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

int my_getline(char **cmd, size_t *len, tcsh_t *term);

int check_history_up(tcsh_t *term, getline_t *st_g);

int check_history_down(tcsh_t *term, getline_t *st_g);

char **parser3000(char *str, char *sep);

int correct_tab(char **tab);

int put_err(char *str);

int left_key(tcsh_t *term, getline_t *st_g);

int right_key(tcsh_t *term, getline_t *st_g);

int all_for_len(tcsh_t *term, history_t *tmp);

int insert_char_at_cursor(getline_t *st_g, tcsh_t *term);

int delete_char_before_cursor(getline_t *st_g, tcsh_t *term);

void move_left(size_t count);

int return_reset(getline_t *st_g);

int ensure_capacity(char **line, size_t *cap, size_t wanted);
char **sweeper(char *str);

int is_parenthesis(char *str);

int is_inihbitor(char *str);

char **translate(char *str);

nodes_t *array_to_node(char **array);

void free_node(nodes_t *head);

int my_fg(tcsh_t *term, char **argv);

int my_bg(tcsh_t *term, char **argv);

int get_max_job_id(tcsh_t *term);

void add_job(tcsh_t *term, pid_t pgid, char *cmd, job_state_t state);

job_t *find_job_id(tcsh_t *term, int id);

job_t *find_job_pid(tcsh_t *term, pid_t pgid);

void remove_job(tcsh_t *term, job_t *job);

void free_jobs(job_t *jobs);

int continue_job_fg(tcsh_t *term, job_t *job);

int continue_job_bg(tcsh_t *term, job_t *job);

int print_return(int fd, const char *str);

int no_such_job(job_t *job, const char *str);

int execute(nodes_t *func, char **command, tcsh_t *term);

int sepecial_variable(tcsh_t *term, char *cmd);

int loops_multi_func(tcsh_t *term, char *cmd, int return_value);

char *check_alias(tcsh_t *term, char *cmd);

int my_alias(tcsh_t *term, char **cmd);

char *search_binary(char *path, char *command);

char *alias(tcsh_t *term, char *cmd);

#endif
