/*
** EPITECH PROJECT, 2025
** include all function
** File description:
** oui
*/

#ifndef MY_LIB
    #define MY_LIB
    #include <stdlib.h>
    #include <unistd.h>
    #include <stdio.h>
    #include <ctype.h>
    #include <string.h>
    #include <fcntl.h>
    #include <signal.h>
    #include <sys/stat.h>
    #include <stdarg.h>
    #include <dirent.h>
    #include <linux/limits.h>
    #include <sys/types.h>
    #include <ctype.h>
    #include <utmp.h>
    #include <sys/wait.h>
    #include <errno.h>
    #include <stdbool.h>

typedef struct nodes {
    void *data;
    struct nodes *next;
} nodes_t;

char **my_str_to_word_array(char *str, char *sp);

int my_str_name(char *str);

char **node_to_array(nodes_t *head);

int len_node(nodes_t *head);

int my_put_nbr(int n);

void free_array(char **array);

int my_read_len(char *file_mane);

char **get_buffer(char *path, char *sep);

char **get_virtual(char *file_path);

int my_str_isnum(char const *str);

int my_getnbr(char const *str);

void push_front(nodes_t **old, nodes_t *new);

int len_array(char **array);

int my_strlen(char const *str);

char *my_strdup(char const *src);

int my_getnbr(char const *str);

int my_strcmp(char const *s1, char const *s2);

char *my_strcat(char *dest, char *src);

void push_back(nodes_t **old, nodes_t *new);

int my_strn(char *str, char *ind);

nodes_t *search_node(nodes_t *head, char *cdt);

char *assembling(char *base, char *sep, char **argv);

int is_it_directory(char *path);

#endif
