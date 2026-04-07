/*
** EPITECH PROJECT, 2025
** digit return
** File description:
** return 1 if it's only digits
*/

int my_str_isnum(char const *str)
{
    if (str[0] == '\0'){
        return (1);
    }
    for (int i = 0; str[i] != '\0'; i++){
        if (str[i] < 48){
            return (0);
        }
        if (str[i] > 58){
            return (0);
        }
    }
    return (1);
}
