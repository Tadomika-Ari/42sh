/*
** EPITECH PROJECT, 2025
** len
** File description:
** compte le nombre de caractère
*/

int my_strlen(char const *str)
{
    int i = 0;

    if (!str)
        return 0;
    for (i = 0; str[i] != 0; i++);
    return (i);
}
