/*
** EPITECH PROJECT, 2026
** hangman
** File description:
** hangman
*/

#include "../../include/struct.h"

static int valid_letters_hangman(char *word)
{
    for (int i = 0; word[i] != '\0'; i++) {
        if (!('a' <= word[i] && word[i] <= 'z'))
            return FALSE;
    }
    return TRUE;
}

char *is_valid_word(void)
{
    char *word = NULL;
    size_t len = 0;
    ssize_t read;

    printf("Write a word, only lower character is authorized\n");
    read = getline(&word, &len, stdin);
    if (read == -1) {
        free(word);
        return NULL;
    }
    word[strcspn(word, "\n")] = '\0';
    if (valid_letters_hangman(word) == FALSE || my_strlen(word) < 2) {
        free(word);
        return NULL;
    }
    return word;
}

static char *blank_word(char *word)
{
    int len = my_strlen(word);
    char *to_find = malloc(sizeof(char) * (len + 1));

    if (!to_find)
        return NULL;
    for (int i = 0; i < len; i++) {
        to_find[i] = '_';
    }
    to_find[len] = '\0';
    return to_find;
}

static void check_letter_hangman(hang_t *hang)
{
    int upd = 0;

    for (int i = 0; hang->ref[i] != '\0'; i++) {
        if (hang->ref[i] == hang->c) {
            hang->to_find[i] = hang->c;
            upd = 1;
        }
    }
    hang->letters[hang->c - 'a'] = 1;
    if (upd == 0)
        hang->hp--;
    if (my_strcmp(hang->ref, hang->to_find) == 0)
        hang->state = DONE;
    printf("%s\n", hang->to_find);
}

static void print_end_hangman(hang_t *hang, char *input)
{
    if (hang->hp <= 0)
        printf("%s\nThe word was %s\n", LOSE_HANGMAN, hang->ref);
    else
        printf("%s\n", WIN_HANGMAN);
    free(input);
}

static int error_hangman(char *input, hang_t *hang)
{
    input[strcspn(input, "\n")] = '\0';
    if (my_strlen(input) != 1 || !('a' <= input[0] && input[0] <= 'z')) {
        printf("Invalid input! Enter a single lowercase letter.\n");
        return FAILURE_EXIT;
    }
    hang->c = input[0];
    if (hang->letters[hang->c - 'a'] == 1) {
        printf("Invalid input! Enter another letter");
        return FAILURE_EXIT;
    }
    check_letter_hangman(hang);
    return SUCCESS_EXIT;
}

void loop_hangman(char *word)
{
    char *to_find = blank_word(word);
    char *input = NULL;
    size_t input_len = 0;
    ssize_t read;
    hang_t hang = {10, to_find, word, RUNNING, '\0'};

    if (!to_find)
        return;
    printf("\033[H\033[2J");
    while (1) {
        if (hang.state != RUNNING || hang.hp <= 0)
            break;
        print_letter_hangman(&hang);
        read = getline(&input, &input_len, stdin);
        if (read == -1)
            break;
        error_hangman(input, &hang);
    }
    print_end_hangman(&hang, input);
    free(to_find);
}

int help_hangman(void)
{
    char *buff = fill_buff_bonus(HANGMAN_HELP);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

char *random_word_hangman(void)
{
    char **tab = NULL;
    char *buff = fill_buff_bonus(HANGMAN_WORDS);

    if (!buff)
        return NULL;
    tab = my_str_to_word_array(buff, "\n\t");
    free(buff);
    if (!tab)
        return NULL;
    buff = my_strdup(tab[rand() % len_array(tab)]);
    free_array(tab);
    return buff;
}

int hangman(tcsh_t *term, char **argv)
{
    char *word = NULL;
    int len = len_array(argv);

    if (len == 1 && (my_strcmp("-h", argv[0]) == 0
            || my_strcmp("--help", argv[0]) == 0))
        return help_hangman();
    if (len == 0)
        word = is_valid_word();
    if (len == 1 && (my_strcmp("--random", argv[0]) == 0)
        || my_strcmp("-r", argv[0]) == 0)
        word = random_word_hangman();
    if (!word)
        return FAILURE_EXIT;
    loop_hangman(word);
    free(word);
    return SUCCESS_EXIT;
}
