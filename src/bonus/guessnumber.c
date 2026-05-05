/*
** EPITECH PROJECT, 2026
** bouns
** File description:
** bonus
*/

#include "../../include/struct.h"

int help_guessnumber(void)
{
    char *buff = fill_buff_bonus(GUESSNUMBER);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

static int ask_number(int nb)
{
    char *input = NULL;
    size_t input_len = 0;
    ssize_t read;
    int n = -1;

    printf(ASK_NUMBER, LEVELS[nb] - 1);
    read = getline(&input, &input_len, stdin);
    if (read == -1)
        return -1;
    n = atoi(input);
    if (n == 0 && my_strlen(input) != 1 && input[0] != '0')
        n = -1;
    if (n < 0)
        n = -1;
    if (my_strcmp("exit\n", input) == 0)
        n = -42;
    free(input);
    return n;
}

int guess_number_n(int nb)
{
    int num = rand() % LEVELS[nb];
    int input = -1;
    int try = 0;

    while (1) {
        input = ask_number(nb);
        if (input == -42)
            break;
        if (input < 0) {
            put_err(WRONG_NUMBER, 84);
            continue;
        }
        try++;
        if (input == num) {
            printf(WINNER_GUESSNUMBER, try);
            break;
        }
        input = (input < num) ? printf("%s", HIGHER) : printf("%s", LOWER);
    }
    return SUCCESS_EXIT;
}

int guess_edit_number(char *number)
{
    int nb = atoi(number);

    if (!(1 <= nb && nb <= 5))
        return put_err(LEVEL_ERR, 84);
    return guess_number_n(nb);
}

int guessnumber(tcsh_t *term, char **argv)
{
    int len = len_array(argv);

    if (len == 1 && (my_strcmp("-h", argv[0]) == 0)
        || my_strcmp("--help", argv[0]) == 0)
        return help_guessnumber();
    if (len == 0) {
        return guess_number_n(DEFAULT_LEVEL);
    }
    if (len == 2 && (my_strcmp("--level", argv[0]) == 0)
        || my_strcmp("-l", argv[0]) == 0) {
        return guess_edit_number(argv[1]);
    }
    return SUCCESS_EXIT;
}
