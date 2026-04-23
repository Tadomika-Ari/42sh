/*
** EPITECH PROJECT, 2026
** 42sh_origin
** File description:
** tests_if
*/

#include "include/struct.h"

int diff(char *val1, char *val2)
{
    if (my_str_isnum(val1) != 0 || my_str_isnum(val2) != 0) {
        if (strcmp(val1, val2) == 0)
            return 1;
        return 0;
    }
    return atoi(val1) != atoi(val2);
}

int egal(char *val1, char *val2)
{
    if (my_str_isnum(val1) != 1 || my_str_isnum(val2) != 1) {
        if (strcmp(val1, val2) == 0)
            return 1;
        return 0;
    }
    return atoi(val1) == atoi(val2);
}

int tall(char *val1, char *val2)
{
    if (atoi(val1) > atoi(val2))
        return 0;
    return 1;
}

int small(char *val1, char *val2)
{
    if (atoi(val1) < atoi(val2))
        return 0;
    return 1;
}

int egal_tall(char *val1, char *val2)
{
    if (atoi(val1) >= atoi(val2))
        return 0;
    return 1;
}

int egal_small(char *val1, char *val2)
{
    if (atoi(val1) <= atoi(val2))
        return 0;
    return 1;
}

int single(char **cmp)
{
    const char *ref[6] = {"!=", "==", "<", ">", "<=", ">="};
    int (*func[])(char *, char *) = {diff, egal, small, tall, egal_small, egal_tall};

    for (int i = 0; ref[i]; i++)
        if (strcmp(ref[i], cmp[1]) == 0) {
            return func[i](cmp[0], cmp[2]);
        }
    return 84;
}

int main(int ac, char **av)
{
    char **cond = my_str_to_word_array(av[1], " )(\t&");

    return 0;
}
