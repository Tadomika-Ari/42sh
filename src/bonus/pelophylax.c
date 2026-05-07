/*
** EPITECH PROJECT, 2026
** pelophylax
** File description:
** pelophylax
*/

#include "../../include/struct.h"

int help_pelophylax(void)
{
    char *buff = fill_buff_bonus(PELOPHYLAX_HELP);

    if (!buff)
        return FAILURE_EXIT;
    printf("%s\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}

int pelophylax(tcsh_t *term, char **argv)
{
    char *buff = NULL;
    int len = len_array(argv);

    if (len == 1 && (my_strcmp("-h", argv[0]) == 0)
        || my_strcmp("--help", argv[0]) == 0)
        return help_pelophylax();
    buff = fill_buff_bonus(PELOPHYLAX);
    if (!buff)
        return FAILURE_EXIT;
    printf("\033[32m%s\033[0m\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}
