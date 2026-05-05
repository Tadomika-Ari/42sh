/*
** EPITECH PROJECT, 2026
** tests
** File description:
** split with exact word separator
*/

#include "my.h"

static void free_split(char **tab, int used)
{
    int i = 0;

    if (!tab)
        return;
    while (i < used) {
        free(tab[i]);
        i++;
    }
    free(tab);
}

static int count_words_by_sep_word(char const *str, char const *sep_word)
{
    int count = 0;
    size_t sep_len = strlen(sep_word);
    size_t str_len = strlen(str);
    char const *p = str;
    char const *next = strstr(p, sep_word);
    size_t len = 0;

    while (next) {
        len = (size_t)(next - p);
        if (len > 0)
            count++;
        p = next + sep_len;
        next = strstr(p, sep_word);
    }
    if (*p != '\0')
        count++;
    if (str_len >= sep_len && strcmp(str + (str_len - sep_len), sep_word) == 0)
        count++;
    return count;
}

static int add_chunk(char **array, int *i, char const *start, size_t len)
{
    if (len == 0)
        return 0;
    array[*i] = strndup(start, len);
    if (!array[*i])
        return -1;
    *i += 1;
    return 0;
}

static int finish_fill(char **array, int i, char const *p, bool trailing_sep)
{
    if (add_chunk(array, &i, p, strlen(p)) == -1) {
        free_split(array, i);
        return -1;
    }
    if (trailing_sep) {
        array[i] = strdup("");
        if (!array[i]) {
            free_split(array, i);
            return -1;
        }
        i++;
    }
    array[i] = NULL;
    return 0;
}

static int fill_array(char **array, char const *str, char const *sep_word)
{
    size_t sep_len = strlen(sep_word);
    size_t str_len = strlen(str);
    char const *p = str;
    char const *next = strstr(p, sep_word);
    size_t len = 0;
    int i = 0;
    bool trailing_sep = false;

    while (next) {
        len = (size_t)(next - p);
        if (add_chunk(array, &i, p, len) == -1) {
            free_split(array, i);
            return -1;
        }
        p = next + sep_len;
        next = strstr(p, sep_word);
    }
    trailing_sep = (str_len >= sep_len &&
        strcmp(str + (str_len - sep_len), sep_word) == 0);
    return finish_fill(array, i, p, trailing_sep);
}

char **my_strtwabw(char *str, char *sep_word)
{
    char **array = NULL;
    int words = 0;

    if (!str || !sep_word || sep_word[0] == '\0')
        return NULL;
    words = count_words_by_sep_word(str, sep_word);
    if (words == 0)
        return NULL;
    array = malloc(sizeof(char *) * (words + 1));
    if (!array)
        return NULL;
    if (fill_array(array, str, sep_word) == -1)
        return NULL;
    return array;
}
