/*
** EPITECH PROJECT, 2026
** bouns
** File description:
** bonus
*/

#include "../../include/struct.h"

int help_throwdice(void)
{
    char *buff = fill_buff_bonus(THROWDICE);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

int throw_dice_n(int n)
{
    int odds = rand() % n;

    odds += DICE_OFFSET;
    printf("%d\n", odds);
    return SUCCESS_EXIT;
}

int throw_edit_dice(char *number)
{
    int nb = atoi(number);

    if (!(7 <= nb && nb <= 20))
        return put_err(NUMBER_FACE_DICE_ERR, 84);
    return throw_dice_n(nb);
}

int throwdice(tcsh_t *term, char **argv)
{
    int len = len_array(argv);

    if (len == 1 && (my_strcmp("-h", argv[0]) == 0)
        || my_strcmp("--help", argv[0]) == 0)
        return help_throwdice();
    if (len == 0) {
        return throw_dice_n(DEFAULT_DICE);
    }
    if (len == 2 && (my_strcmp("--face", argv[0]) == 0)
        || my_strcmp("-f", argv[0]) == 0) {
        return throw_edit_dice(argv[1]);
    }
    return SUCCESS_EXIT;
}
