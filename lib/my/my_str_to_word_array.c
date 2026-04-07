/*
** EPITECH PROJECT, 2025
** str array
** File description:
** put word into array
*/

#include <stdlib.h>
#include <stdio.h>

static int alpha(char asc, char *sep)
{
    for (int i = 0; sep[i] != 0; i++){
        if (asc == sep[i])
            return (0);
    }
    return (1);
}

static int len_word(char *str, char *sep)
{
    int len = 0;
    int bo = 0;

    for (int index = 0; str[index] != '\0'; index++){
        if (bo == 0 && alpha(str[index], sep) == 1){
            len++;
            bo = 1;
        }
        if (alpha(str[index], sep) == 0)
            bo = 0;
    }
    return (len);
}

static char *my_ajout(int len, char *sep, char *array, char const *str)
{
    int ind = 0;
    int i = 0;

    for (i = len; alpha(str[i], sep) == 1 && str[i] != 0; i++);
    array = malloc(sizeof(char) * ((i + 1) - (len)));
    if (!array)
        return NULL;
    for (int to = len; alpha(str[to], sep) == 1 && str[to] != '\0'; to++){
        array[ind] = str[to];
        ind++;
    }
    array[ind] = '\0';
    return array;
}

int verification(char **array, char const *str, char *sp)
{
    int bo = 0;
    int len = 0;
    int word = 0;

    for (int i = 0; str[i] != '\0'; i++){
        if (bo == 0 && alpha(str[i], sp) == 1){
            len = i;
            bo = 1;
            word++;
        }
        if (bo == 1 && alpha(str[i], sp) == 0 || bo == 1 && str[i + 1] == '\0'){
            array[word - 1] = my_ajout(len, sp, array[word - 1], str);
            bo = 0;
        }
    }
    return 0;
}

char **my_str_to_word_array(char *str, char *sp)
{
    char **array = NULL;

    if (str == NULL || str[0] == 0 || len_word(str, sp) == 0)
        return NULL;
    array = malloc(sizeof(char*) * (len_word(str, sp) + 1));
    if (!array)
        return NULL;
    array[len_word(str, sp)] = NULL;
    verification(array, str, sp);
    return array;
}
