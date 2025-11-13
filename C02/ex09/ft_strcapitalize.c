#include <stdio.h>

int is_lower(char c){
    return (c >= 'a' && c <= 'z');
}

int is_upper(char c){
    return (c >= 'A' && c <= 'Z');
}

int is_number(char c){
    return (c >= '0' && c <= '9');
}

int is_alphanumeric(char c){
    return (is_lower(c) || is_upper(c) || is_number(c));
}

char *ft_strcapitalize(char *str){

    int  i;

    i = 0;
    while (str[i] != '\0'){

        int prev_is_alnum = ((i > 0) && is_alphanumeric(str[i - 1]));

        if (is_lower(str[i]) && !prev_is_alnum)
            str[i] -= 32;

        if (is_upper(str[i]) && prev_is_alnum)
            str[i] += 32;

        i++;
    }

    return (str);
}

int main(){
    char str[] = "salut, comment tu vas ? 42mots quarante-deux; cinquante+et+un";

    printf("Before: %s\n", str);
    printf("After : %s\n", ft_strcapitalize(str));

    return (0);
}
