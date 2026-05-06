/*
** EPITECH PROJECT, 2026
** glob
** File description:
** glob
*/

#include "../../include/struct.h"
#include <glob.h>

char **dup_array(char **arr, glob_t *globstruct)
{
    int len = len_array(arr);
    char **new = NULL;

    if (len > 0)
        new = malloc(sizeof(char *) * (len + 1));
    if (!new) {
        globfree(globstruct);
        return new;
    }
    for (int i = 0; i < len; i++) {
        new[i] = my_strdup(arr[i]);
    }
    new[len] = NULL;
    globfree(globstruct);
    return new;
}

char **globbing(char *str)
{
    char **res = NULL;
    glob_t globstruct;

    if (glob(str, GLOB_ERR, NULL, &globstruct) != 0)
        return NULL;
    res = globstruct.gl_pathv;
    if (!res)
        res = array_null('\0');
    return dup_array(res, &globstruct);
}

int is_globing(char *str)
{
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == '*' || str[i] == '[')
            return TRUE;
        if (str[i] == '?' || str[i] == ']')
            return TRUE;
    }
    return FALSE;
}
