/*
** EPITECH PROJECT, 2026
** hangman
** File description:
** hangman
*/

#include "../../include/struct.h"

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
    printf("%s\n", word);
    return word;
}

int help_hangman(void)
{
    char *buff = fill_buff_bonus(HANGMAN);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

int hangman(tcsh_t *term, char **argv)
{
    char *word = NULL;
    int len = len_array(argv);

    if (len == 1 && my_strcmp("-h", argv[0]) == 0)
        return help_hangman();
    word = is_valid_word();
    if (!word)
        return FAILURE_EXIT;
    return SUCCESS_EXIT;
}
