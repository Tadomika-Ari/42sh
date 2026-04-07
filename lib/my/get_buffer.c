/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** get_buffer
*/

#include "my.h"

char **get_buffer(char *path, char *sep)
{
    int fd = open(path, O_RDONLY);
    struct stat file_stat;
    char *buffer;
    char **res;

    if (stat(path, &file_stat) == -1)
        return NULL;
    buffer = malloc(sizeof(char) * (file_stat.st_size + 1));
    if (fd == -1 || !buffer || read(fd, buffer, file_stat.st_size) == -1)
        return NULL;
    buffer[file_stat.st_size] = 0;
    close(fd);
    res = my_str_to_word_array(buffer, sep);
    free(buffer);
    return res;
}

static char **free_error(char *str, int fd)
{
    if (str)
        free(str);
    if (fd >= 0)
        close(fd);
    return NULL;
}

char **get_virtual(char *file_path)
{
    int size = my_read_len(file_path);
    int fd = open(file_path, O_RDONLY);
    int rd = 0;
    char *str = NULL;
    char **res = NULL;

    if (size == -1 || fd == -1 || size == 0)
        return free_error(str, fd);
    str = malloc(sizeof(char) * (size + 1));
    if (str == NULL)
        return free_error(str, fd);
    rd = read(fd, str, size);
    if (rd == -1)
        return free_error(str, fd);
    str[rd] = '\0';
    res = my_str_to_word_array(str, " \t\n");
    free_error(str, fd);
    return res;
}
