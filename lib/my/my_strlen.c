/*
** EPITECH PROJECT, 2025
** len
** File description:
** compte le nombre de caractère
*/

int my_strlen(char const *str)
{
    int i;

    for (i = 0; str[i] != 0; i++);
    return (i);
}
