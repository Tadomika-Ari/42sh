/*
** EPITECH PROJECT, 2026
** check_alias
** File description:
** check_alias
*/

#include "../../include/struct.h"

static char *strip_single_quotes(char *word)
{
    int len = 0;
    char *result = NULL;

    if (word == NULL)
        return NULL;
    len = my_strlen(word);
    if (len >= 2 && word[0] == '\'' && word[len - 1] == '\'') {
        result = malloc(len - 1);
        if (result == NULL)
            return NULL;
        for (int i = 1; i < len - 1; i++)
            result[i - 1] = word[i];
        result[len - 2] = '\0';
        return result;
    }
    return my_strdup(word);
}

char *get_rc_file(tcsh_t *term)
{
    int fd;
    struct stat sb;
    char *buf = NULL;

    fd = open(RC_FILE, O_RDONLY);
    if (fd == FAILURE_EXIT)
        return NULL;
    if (stat(RC_FILE, &sb) == FAILURE_EXIT)
        return NULL;
    buf = malloc(sb.st_size + 1);
    if (buf == NULL)
        return NULL;
    read(fd, buf, sb.st_size);
    buf[sb.st_size] = '\0';
    close(fd);
    return buf;
}

char *check_alias(tcsh_t *term, char *cmd)
{
    char *buf = get_rc_file(term);
    char **tab = NULL;
    char *alias = NULL;

    if (buf == NULL)
        return NULL;
    tab = parser3000(buf, "# =\n");
    if (tab == NULL) {
        free(buf);
        return NULL;
    }
    for (int i = 0; tab[i] != NULL && tab[i + 1] != NULL && tab[i + 2] != NULL
        ; i += 3)
        if (my_strcmp(tab[i], "alias") == 0 && my_strcmp(tab[i + 1], cmd) == 0)
            alias = strip_single_quotes(tab[i + 2]);
    free_array(tab);
    free(buf);
    return alias;
}

int main(void)
{
    char *alias = NULL;

    alias = check_alias(NULL, "cwdcmd");
    if (alias != NULL)
        printf("%s\n", alias);
    free(alias);
    return 0;
}
