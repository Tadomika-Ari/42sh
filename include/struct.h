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
    #include <time.h>
    #define INITIAL_CAPACITY 128
    #define MAX_LINE 1024


    #define RC_FILE "./bonus/.42rc"

    #define UNMATCH_SINGLE "Unmatched '''.\n"
    #define UNMATCH_QUOTE "Unmatched '\"'.\n"
    #define UNMATCH_BACK "Unmatched '`'.\n"
    #define MANY_CLOSE "Too many )'s.\n"
    #define MANY_OPEN "Too many ('s.\n"
    #define NULL_CMD "Invalid null command.\n"

    #define CMD_NOT_FOUND ": Command not found.\n"
    #define NO_MATCH ": No match.\n"
    #define EXPRESSION_SYNTAX ": Expression Syntax.\n"
    #define TOO_FEW ": Too few arguments.\n"
    #define TOO_MANY ": Too many arguments.\n"
    #define NO_SUCH ": No such file or directory.\n"
    #define EXEC_FORMAT ": Exec format error. Binary file not executable.\n"
    #define VAR_NAME ": Variable name must begin with a letter.\n"
    #define AMBIGOUS_OUTPUT "Ambiguous output redirect.\n"
    #define VAR_MUST ": Variable name must contain alphanumeric characters.\n"
    #define NOT_DIR ": Not a directory.\n"
    #define ARG_NOT_SUP ": Argument not supported.\n"
    #define NO_HOME ": No home directory.\n"
    #define PERMISSION_DENIED ": Permission denied.\n"

    #define SEP "()[]'\"`"

    #define PELOPHYLAX_HELP "./bonus/pelophylax_help.txt"
    #define HANGMAN_HELP "./bonus/hangman.txt"
    #define FLIPCOIN_HELP "./bonus/flipcoin.txt"
    #define THROWDICE_HELP "./bonus/throwdice.txt"
    #define GUESSNUMBER_HELP "./bonus/guessnumber.txt"

    #define AUTHOR "./bonus/author.txt"
    #define PELOPHYLAX "./bonus/pelophylax.txt"
    #define RICKROLL "./bonus/rickroll.txt"

    #define HANGMAN_WORDS "./bonus/hangman_words.txt"

    #define ASK_LETTER "Choose a letter: "
    #define WIN_HANGMAN "You win the game!"
    #define LOSE_HANGMAN "You lose the game!"

    #define HEAD HEAD_TOP HEAD_CENTER HEAD_BOT
    #define HEAD_TOP "  ______  \n /      \\ \n"
    #define HEAD_CENTER "|  HEAD |\n|       |\n"
    #define HEAD_BOT " \\______/ \n"

    #define TAIL TAIL_TOP TAIL_CENTER TAIL_BOT
    #define TAIL_TOP "  ______  \n /      \\ \n"
    #define TAIL_CENTER "|  TAIL |\n|       |\n"
    #define TAIL_BOT " \\______/ \n"

    #define NB_STEP 11
    #define NB_ROW 7
extern const char *STEPS[NB_STEP][NB_ROW];

    #define DEFAULT_DICE 6
    #define NUMBER_FACE_DICE_ERR "throwdice: wrong number value, [7; 20]\n"
    #define DICE_OFFSET 1

    #define DEFAULT_LEVEL 0
    #define LEVEL_ERR "numberguesser: wrong number value, [1; 5]\n"
    #define LEVELS (int[]){10, 100, 1000, 10000, 100000, 1000000}
    #define WINNER_GUESSNUMBER "You guessed the right number in %d tries\n"
    #define LOWER "Try lower\n"
    #define HIGHER "Try higher\n"
    #define ASK_NUMBER "Enter a number between 0 and %d: "
    #define WRONG_NUMBER "Wrong number, try again\n"

    #define INCORECT_POS ERROR SOL
    #define SOL "ROWS [A,B,C] and COLS [1,2,3]\n"
    #define ERROR "Incorect Pos \"RowCol\" ex \"A1\" or \"1A\" "

    #define BLACK "\e[30m"
    #define RED "\e[31m"
    #define GREEN "\e[32m"
    #define YELLOW "\e[33m"
    #define BLUE "\e[34m"
    #define MAGENTA "\e[35m"
    #define CYAN "\e[36m"
    #define WHITE "\e[37m"
    #define NORMAL "\e[m"

    #define PLAYER1 1
    #define PLAYER2 2

    #define COLS "123"
    #define ROWS "ABC"

    #define SOUND_STRUCT "ffmpeg -loglevel quiet -i %s" SOUND_STRUCT_END
    #define SOUND_STRUCT_END " -f wav - | paplay > /dev/null 2>&1"
    #define MAMBO_SONG "./bonus/songs/mambo.mp3"
    #define YIPPEE_SONG "./bonus/songs/yippee.mp3"
    #define RICKROLL_SONG "./bonus/songs/rickroll.mp3"
    #define RICKROLL_ODDS 5

typedef struct alias {
    char *name_alias;
    char *cmd_alias;
} alias_t;

typedef struct alias_tool {
    char *new_expanded;
    char *expanded;
    char *prev_first_word;
    char *curr_first_word;
    nodes_t *alias_histo;
} alias_tool_t;

typedef enum exit
{
    SUCCESS_EXIT = 0,
    ALT_EXIT = -1,
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
    int len_u;
    int len_d;
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
    nodes_t *locals;
    char *return_value;
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
    bool is_background;
    int nb_repeat;
    int is_repeat;
    int nb_nb_repeat;
    int error_repeat;
    nodes_t *alias;
} tcsh_t;

typedef struct function {
    const char *name;
    int (*cmd)(tcsh_t *, char **);
} function_t;

typedef struct locals {
    char *name;
    char *value;
} locals_t;

typedef struct parse {
    int in_quote;
    int in_tick;
    int in_btick;
    int parent;
    int brack;
    int count;
    int start;
    int i;
    int in_var;
} parse_t;

typedef struct ele {
    int i;
    int count;
    int start;
} ele_t;

typedef struct tic_tac_toe {
    int state;
    char **gride;
    int player;
    int posx;
    int posy;
    int turn;
    int player_win;
    int gride_int[9];
} ttt_t;

typedef struct hang {
    int hp;
    char *to_find;
    char *ref;
    int state;
    char c;
    int letters[26];
} hang_t;

typedef struct job_control_count {
    int i;
    int position;
    int nb_cmd;
    char *separators;
} jobs_cont_t;

typedef struct job_control_exec {
    int ignore;
    int or_done;
    int value;
} jobs_exec_t;

int init(tcsh_t *term, char **env);

int fill_rc(tcsh_t *term);

nodes_t *new_node(void *data);

void free_locals(locals_t *locals);

int my_set(tcsh_t *term, char **argv);

int error_alphanumeric(char *cmd);

int error_not_enough_argument(char *cmd);

int error_too_many_argument(char *cmd);

int error_permission_denied(char *cmd);

int error_first_caracter(char *cmd);

int apply(tcsh_t *term, char **cmd);

int execute_cmd(tcsh_t *term, char **argv);

int error_no_home(char *cmd);

int exec_else_if(char **lign, char **action, tcsh_t *term, int *cond);

int exec_if(char **lign, char **action, tcsh_t *term, int *cond);

int exec_else(char **lign, char **action, tcsh_t *term, int *cond);

int is_then(char **argv);

char **dupl_array(char **argv);

int search_condition(tcsh_t *term, char **argv, bool *error);

int command_not_found(char *cmd);

int search_variable(tcsh_t *term, nodes_t *str);

int path_not_found(char *path);

int error_syntax(char *cmd);

int env(tcsh_t *term, char **argv);

char *simple(char c);

int my_cmd_error(char *str, char *cmd, int out);

int my_which(tcsh_t *term, char **argv);

int my_cd(tcsh_t *term, char **argv);

void algo_exit(int *result);

int not_cond(char *str);

int join_len_until_then(char **argv);

int fallback_cond(tcsh_t *term, char *cond, bool *error);

char *search_bin(tcsh_t *term, char *command);

int normalize(tcsh_t *term, char *cmd, char **command, int status);

int error_expression_syntax(char *cmd);

nodes_t *create_new_node(char *lign_env);

int my_exit(tcsh_t *term, char **argv);

char *take_value(nodes_t *head, char *cat);

int my_setenv(tcsh_t *term, char **argv);

void my_free_exist(void *pointer);

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

int correct_name(char *name, char *cmd);

int correct_tab(char **tab);

int put_err(char *str, int flags);

int left_key(tcsh_t *term, getline_t *st_g);

int right_key(tcsh_t *term, getline_t *st_g);

int all_for_len(tcsh_t *term, history_t *tmp);

int insert_char_at_cursor(getline_t *st_g, tcsh_t *term);

int delete_char_before_cursor(getline_t *st_g, tcsh_t *term);

void move_left(size_t count);

int return_reset(getline_t *st_g);

int ensure_capacity(char **line, size_t *cap, size_t wanted);

char **sweeper(tcsh_t *term, char *str, bool *error);

int is_parenthesis(char *str);

int is_inihbitor(char *str);

char **translate(tcsh_t *term, nodes_t *str, bool *error);

nodes_t *array_to_node(char **array);

void free_node(nodes_t *head);

char *get_name(char *str, int max);

char *without(char *str);

char *my_str_rea(char *base, char *value);

char **array_null(char c);

int search_command(tcsh_t *term, char **command, char *cmd);

int my_fg(tcsh_t *term, char **argv);

int my_if(tcsh_t *term, char **argv);

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

int loops_multi_func(tcsh_t *term, char *cmd, int return_value);

char *check_alias(tcsh_t *term, char *cmd);

int my_alias(tcsh_t *term, char **cmd);

int from_one_line(tcsh_t *term, char *cmd);

char *read_fd(int pipefd[2]);

char *backsticks(tcsh_t *term, char *command);

int search_backsticks(tcsh_t *term, nodes_t *str);

char *search_binary(char *path, char *command);

char *alias(tcsh_t *term, char *cmd);

int display_alias(char *cmd, char *value);

int display_built(char *cmd);

int my_where(tcsh_t *term, char **argv);

char *get_rc_file(tcsh_t *term);

char *strip_single_quotes(char *word);

int check_repeat(char *av, tcsh_t *term);

int my_foreach(tcsh_t *term, char **argv);

int my_lenbase(int nb, int base);

char *cut_len(char *str, int nbr);

int repeat_or_no_repeat(tcsh_t *term, char *cmd, int value);

int is_only_spaces(const char *cmd);

int check_error(tcsh_t *term, char *cmd, int value);

int fail_repeat_check(tcsh_t *term, char *cmd, int value);

char *strip_quotes(char *word);

void *my_puterror_ptr(char *message);

void show_array(char **tab);

int is_sep(char c, char *sep);

void update_state(parse_t *parse, char c);

void update_other(parse_t *parse, char c);

int is_protected(parse_t *parse);

nodes_t *create_new_node(char *lign_env);

nodes_t *new_node(void *data);

int fill_bonus(tcsh_t *term);

int push_function(tcsh_t *term,
    int (*cmd)(tcsh_t *, char **), const char *name);

int pelophylax(tcsh_t *term, char **argv);

char **globbing(char *str);

int is_globing(char *str);

char **array_null(char c);

int hangman(tcsh_t *term, char **argv);

char *fill_buff_bonus(const char *filename);

void print_letter_hangman(hang_t *hang);

int cprintf(char *str, char *color);

char *fill_buff(const char *filename);

char *my_strip_newline(char *str);

int tic_tac_toe(tcsh_t *term, char **argv);

int flipcoin(tcsh_t *term, char **argv);

int throwdice(tcsh_t *term, char **argv);

int guessnumber(tcsh_t *term, char **argv);

int autocompletation(tcsh_t *term, getline_t *st_g);

int author(tcsh_t *term, char **argv);

void *ret_error_alias(alias_tool_t *tmp);

alias_tool_t init_alias_tool(char *cmd);

void free_prev_cur(char *prev, char *cur);

void free_alias_history(nodes_t *alias_histo);

int occ_in_str(char c, char *str);

int check_parenthesis(char *str);

int check_quotes(char *str);

int check_back(char *str);

int play_sound(char *filename);

int mambo(tcsh_t *term, char **argv);

char **take_action(bool *error, const char *end);

int yippee(tcsh_t *term, char **argv);

int job_control(tcsh_t *term, char *cmd);

int job_execution(tcsh_t *term, jobs_exec_t *sta,
    char **cmds, char **jobs);

int empty_error_case(char **commands, char **jobs);

int empty_cmd_detect(char *cmd);

void update_ele(ele_t *ele);

int rickroll(void);
#endif
