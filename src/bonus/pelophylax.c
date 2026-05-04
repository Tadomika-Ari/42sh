/*
** EPITECH PROJECT, 2026
** pelophylax
** File description:
** pelophylax
*/

#include "../../include/struct.h"

char *fill_pelophylax(void)
{
    int fd = open(PELOPHYLAX, O_RDONLY);
    char *buff = NULL;
    struct stat st;
    int size = 0;

    if (fd == -1)
        return NULL;
    if (stat(PELOPHYLAX, &st) == -1)
        return NULL;
    buff = malloc(sizeof(char) * (st.st_size + 1));
    size = read(fd, buff, st.st_size);
    buff[size] = '\0';
    close(fd);
    return buff;
}

int pelophylax(tcsh_t *term, char **argv)
{
    char *buff = fill_pelophylax();

    if (!buff)
        return FAILURE_EXIT;
    printf("\033[32m%s\033[0m\n", buff);
    free(buff);
    return SUCCESS_EXIT;
}
