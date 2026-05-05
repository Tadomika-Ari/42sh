/*
** EPITECH PROJECT, 2026
** tic_tac_toe
** File description:
** tic_tac_toe
*/

#include "../../include/struct.h"

char **init_gride(void)
{
    char **tmp = malloc(sizeof(char *) * (3 + 1));

    if (tmp == NULL)
        return NULL;
    tmp[3] = NULL;
    for (int i = 0; i < 3; i++) {
        tmp[i] = my_strdup("***");
        if (tmp[i] == NULL)
            return NULL;
    }
    return tmp;
}

void print_gride(char **gride)
{
    printf("    1 | 2 | 3 \n");
    printf("  ----|---|---\n");
    printf("  A %c | %c | %c \n", gride[0][0], gride[0][1], gride[0][2]);
    printf("  ----|---|---\n");
    printf("  B %c | %c | %c \n", gride[1][0], gride[1][1], gride[1][2]);
    printf("  ----|---|---\n");
    printf("  C %c | %c | %c \n", gride[2][0], gride[2][1], gride[2][2]);
    printf("  ----|---|---\n");
}

int run_game(void)
{
    size_t input_len = 0;
    ssize_t read;
    char *input = NULL;
    ttt_t ttt = {RUNNING, NULL};

    ttt.gride = init_gride();
    ttt.player = PLAYER1;
    for (int i = 0; i < 9; i++)
        ttt.gride_int[i] = 0;

    while (1) {
        if (ttt.state != RUNNING)
            break;
        printf("\033[H\033[2J");
        print_gride(ttt.gride);
        printf("Player %d Turn : ", ttt.player);
        read = getline(&input, &input_len, stdin);
        if (read == -1)
            break;
        
    }
    return SUCCESS_EXIT;
}

int help(void)
{
    char *buf = fill_buff("bonus/tic_tac_toe.txt");

    cprintf(buf, BLUE);
    return SUCCESS_EXIT;
}

int tic_tac_toe(tcsh_t *term, char **argv)
{
    if (my_strcmp(argv[0], "-h") == 0)
        return help();
    return run_game();
}

int main(int ac, char **av)
{
    return tic_tac_toe(NULL, av);
}
