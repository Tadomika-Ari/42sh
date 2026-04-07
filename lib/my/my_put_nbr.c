/*
** EPITECH PROJECT, 2025
** put nmb
** File description:
** met des nombre
*/

#include <unistd.h>

int my_put_nbr(int n)
{
    char c;

    if (n >= 10)
        my_put_nbr(n / 10);
    c = (n % 10) + '0';
    write(1, &c, 1);
    return 0;
}
