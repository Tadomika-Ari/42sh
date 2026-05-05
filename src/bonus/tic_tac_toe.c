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

int get_pos(char *pos, ttt_t *ttt)
{
    if (my_strlen(pos) != 2)
        return put_err("Incorect Pos \"RowCol\" ex \"A1\" or \"1A\" ROWS [A,B,C] and COLS [1,2,3]\n", -1);
    ttt->posx = -1;
    ttt->posy = -1;
    for (int i = 0; i < 3; i++)
        if (pos[0] == COLS[i] || pos[1] == COLS[i])
            ttt->posx = i;
    for (int i = 0; i < 3; i++)
        if (pos[0] == ROWS[i] || pos[1] == ROWS[i])
            ttt->posy = i;
    if (ttt->posy == -1 || ttt->posx == -1)
        return put_err("Incorect Pos \"RowCol\" ex \"A1\" or \"1A\" ROWS [A,B,C] and COLS [1,2,3]\n", -1);
    return SUCCESS_EXIT;
}

void print_gride(char **gride, int player, ttt_t *ttt)
{
    printf("\nPlayer 1 = X  Player 2 = O \n\n");
    printf("    1 | 2 | 3 \n");
    printf("  ----|---|---\n");
    printf("  A %c | %c | %c \n", gride[0][0], gride[0][1], gride[0][2]);
    printf("  ----|---|---\n");
    printf("  B %c | %c | %c \n", gride[1][0], gride[1][1], gride[1][2]);
    printf("  ----|---|---\n");
    printf("  C %c | %c | %c \n", gride[2][0], gride[2][1], gride[2][2]);
    printf("  ----|---|---\n");
    if (ttt->player_win == -1 && ttt->turn != 0)
        printf("\nturn : %d \nPlayer %d Turn : ", ttt->turn, player);
}

int set_in_gride(ttt_t *ttt) 
{
    char c = 'X';

    if (ttt->player == 2)
        c = 'O';
    if (ttt->gride_int[ttt->posx + (3 * ttt->posy)] == 0) { 
        ttt->gride_int[ttt->posx + (3 * ttt->posy)] = ttt->player;
        ttt->gride[ttt->posy][ttt->posx] = c;
    }
    else
        return put_err("This space is occupied. Start over.\n", ttt->player);
    if (ttt->player == PLAYER1)
        return PLAYER2;
    return PLAYER1;
}

int algo_end(ttt_t *ttt)
{
    int turn = 0;

    for (int i = 0; i < 9; i++)
        if (ttt->gride_int[i] == 0)
            turn++;
    ttt->turn = turn;
    if (ttt->gride_int[4] != 0 && (ttt->gride_int[4] == ttt->gride_int[0] && ttt->gride_int[4] == ttt->gride_int[8]))
        return ttt->gride_int[4];
    if (ttt->gride_int[4] != 0 && (ttt->gride_int[4] == ttt->gride_int[2] && ttt->gride_int[4] == ttt->gride_int[6]))
        return ttt->gride_int[4];
    for (int i = 0; i < 3; i++)
        if (ttt->gride_int[i] != 0 && (ttt->gride_int[i + 0] == ttt->gride_int[i + 3] && ttt->gride_int[i + 3] == ttt->gride_int[i + 6]))
            return ttt->gride_int[4];
    for (int i = 0; i < 9; i += 3)
        if (ttt->gride_int[i] != 0 && (ttt->gride_int[i] == ttt->gride_int[i + 1] && ttt->gride_int[i + 1] == ttt->gride_int[i + 2]))
            return ttt->gride_int[4];
    return -1;
}

int run_game(void)
{
    size_t input_len = 0;
    ssize_t read;
    char *input = NULL;
    ttt_t ttt = {RUNNING, NULL, PLAYER1, -1, -1, 9, -1};

    ttt.gride = init_gride();
    for (int i = 0; i < 9; i++)
        ttt.gride_int[i] = 0;
    print_gride(ttt.gride, ttt.player, &ttt);
    while (1) {
        if (ttt.state != RUNNING)
            break;
        read = getline(&input, &input_len, stdin);
        if (read == -1)
            break;
        input[strcspn(input, "\n")] = '\0';
        if (get_pos(input, &ttt) != -1)
            ttt.player = set_in_gride(&ttt);
        ttt.player_win = algo_end(&ttt);
        print_gride(ttt.gride, ttt.player, &ttt);
        if (ttt.player_win != -1 || ttt.turn == 0)
            break;
    }
    if (ttt.player_win != -1)
        printf("Player %d WIN!!!!\n", ttt.player_win);
    if (ttt.turn == 0)
        printf("Draw\n");
    return SUCCESS_EXIT;
}

int help(void)
{
    char *buf = fill_buff("bonus/tic_tac_toe.txt");

    cprintf(buf, YELLOW);
    return SUCCESS_EXIT;
}

int tic_tac_toe(tcsh_t *term, char **argv)
{
    if ((my_strcmp("-h", argv[0]) == 0
            || my_strcmp("--help", argv[0]) == 0))
        return help();
    return run_game();
}
