/*
** EPITECH PROJECT, 2026
** bouns
** File description:
** bonus
*/

#include "../../include/struct.h"

int help_flipcoin(void)
{
    char *buff = fill_buff_bonus(FLIPCOIN_HELP);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

int flipcoin(tcsh_t *term, char **argv)
{
    int odds = rand() % 2;
    int len = len_array(argv);
    int tmp = 0;

    if (len == 1 && (my_strcmp("-h", argv[0]) == 0)
        || my_strcmp("--help", argv[0]) == 0)
        return help_flipcoin();
    if (len == 0) {
        tmp = (odds == 0) ? (printf("Tail\n")) : printf("Head\n");
    }
    if (len == 1 && (my_strcmp("--visualisation", argv[0]) == 0)
        || my_strcmp("-v", argv[0]) == 0) {
        tmp = (odds == 0) ? printf("%s", TAIL) : printf("%s", HEAD);
    }
    return SUCCESS_EXIT;
}
