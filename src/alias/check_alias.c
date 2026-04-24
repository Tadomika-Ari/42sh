/*
** EPITECH PROJECT, 2026
** check_alias
** File description:
** check_alias
*/

#include "../../include/struct.h"

char *get_rc_file(tcsh_t *term)
{
    int fd ;
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

char *check_alias(tcsh_t *term, char *alias)
{
    char *buf = get_rc_file(term);
    char **tab = NULL;

    if (buf == NULL)
        return NULL;
    tab = parser3000(buf, " \n");
    if (tab == NULL) {
        free(buf);
        return NULL;
    }
    for (int i = 0; tab[i] != NULL; i++)
        printf("(%s)", tab[i]);
    free_array(tab);
    return buf;
    
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
