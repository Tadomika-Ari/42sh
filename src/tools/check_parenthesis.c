/*
** EPITECH PROJECT, 2026
** check
** File description:
** check
*/

#include "../../include/struct.h"

static int pos_str(char c, char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c)
            return i;
    }
    return -1;
}

int check_parenthesis(char *str)
{
    int op = occ_in_str('(', str);
    int cl = occ_in_str(')', str);
    int tmp = 0;

    if (my_strlen(str) == 2 && (str[0] == '(' && str[1] == ')'))
        return put_err(NULL_CMD, TRUE);
    if (pos_str('(', str) > pos_str(')', str))
        return put_err(MANY_CLOSE, TRUE);
    if (op != cl)
        return (op > cl) ? put_err(MANY_OPEN, TRUE) : put_err(MANY_CLOSE, TRUE);
    return FALSE;
}
