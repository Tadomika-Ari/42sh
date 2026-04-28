/*
** EPITECH PROJECT, 2026
** init
** File description:
** init
*/

#include "../../include/struct.h"

int fill_rc(tcsh_t *term)
{
    term->fd_rc = open(RC_FILE, O_CREAT | O_RDWR, 0644);
    if (term->fd_rc == -1) {
        return EXIT_FAILURE;
    }
    return EXIT_SUCCESS;
}
