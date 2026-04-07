/*
** EPITECH PROJECT, 2026
** my_top
** File description:
** file_len
*/

#include "my.h"

int my_read_len(char *file_name)
{
    FILE *file = fopen(file_name, "r");
    int size = 0;
    int c;

    if (!file)
        return -1;
    for (c = fgetc(file); c != EOF; c = fgetc(file))
        size++;
    fclose(file);
    return size;
}
