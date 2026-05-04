/*
** EPITECH PROJECT, 2026
** bonus
** File description:
** bonus
*/

#include "../../include/struct.h"

char *fill_buff_bonus(const char *filename)
{
    int fd = open(filename, O_RDONLY);
    char *buff = NULL;
    struct stat st;
    int size = 0;

    if (fd == -1)
        return NULL;
    if (stat(filename, &st) == -1)
        return NULL;
    buff = malloc(sizeof(char) * (st.st_size + 1));
    size = read(fd, buff, st.st_size);
    buff[size] = '\0';
    close(fd);
    return buff;
}
