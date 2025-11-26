#include <unistd.h>
#include <stdio.h>

int ft_atoi(char *str){ int result;
	int minus_count;

	result = 0;
	minus_count = 0;

	minus_count = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		str++;

	while (*str == '+' || *str == '-'){

		if (*str == '-')
			minus_count++;

		str++;
	}
	
	while (*str >= '0' && *str <= '9'){
		result = result * 10 + (*str - '0');
		 str++;
	}

	return ((minus_count % 2) ? -result : result); 
}

/*
int ft_atoi(char *str){
	int i;
	int sign;
	int result;

	i = 0;
	sign = 1;
	result = 0;
	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (result * sign);
}
*/

int main(){
	char str1[] = " ---+--+1234ab567";
	char str2[] = "  42";
	char str3[] = "-2147483648";

	printf("%d\n", ft_atoi(str1));
	printf("%d\n", ft_atoi(str2));
	printf("%d\n", ft_atoi(str3));


	return (0);
}

/*

void ft_putchar(char c){
	write(1, &c, 1);
}

int is_space(char *space){
	return (*space == ' ');
}

int num_posi_sign(char *posi){
	return (*posi == '+');
}

int num_nega_sign(char *minu){
	return (*minu == '-');
}

int is_num(char *num){
	return ((*num >= '0' && *num <= '9'));
}

int is_alph(char *alph){
	return ((*alph >= 'A' && *alph <= 'Z') || (*alph >= 'a' && *alph <= 'z'));
}

int ft_atoi(char *str){
	int i;
	int result;
	int minus_sign;

	i = 0;
	while (str[i] != '\0' && is_space(&str[i]))
		i++;

	minus_sign = 0;
	while (str[i] != '\0' && (num_posi_sign(&str[i]) || num_nega_sign(&str[i]))){
		if (num_nega_sign(&str[i]))
			minus_sign++;
		i++;
	}

	result = 0;
	while (str[i] != '\0' && is_num(&str[i])){
		result = result * 10 + (str[i] - '0');	
		i++;
	}
	
	if (minus_sign % 2 != 0)
		result *= -1;

	return (result);
}
*/
