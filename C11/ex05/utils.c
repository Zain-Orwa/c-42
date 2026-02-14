/* utils.c */
#include "do_op.h"

int is_white_space(char c){ 
	return (c == ' ' || (c >= 9 && c <= 13));
}

int is_digit(char c){ 
	return (c >= '0' && c <= '9');	
}

int is_operator(char c){ 
	return (c == '+' || c == '-' || c == '*' || c == '/' || c == '%');
}

int ft_atoi(char *str){ 
	int i; 
	int sign; 
	int result; 

	i = 0; 
	sign = 1; 
	result = 0; 
	while (str[i] && is_white_space(str[i])) 
		i++; 
	while (str[i] == '+' || str[i] == '-') 
	{ 
		if (str[i] == '-') 
			sign *= -1; 
		i++; 
		
	} 
	while (str[i] && is_digit(str[i])) 
	{ 
		result = result * 10 + (str[i] - '0'); 
		i++; 
		
	} 
	return (result * sign);
}

void ft_putchar(char c){ 
	write(1, &c, 1);
}

void ft_putstr(char *str){ 
	int i; 

	if (!str) 
		return ; 

	i = 0; 
	while (str[i]){ 
		ft_putchar(str[i]); 
		i++; 
	}
}

void ft_putnbr(int nbr){ 
	long num; 

	num = nbr; 
	if (num < 0) 
	{ 
		ft_putchar('-'); 
		num = -num; 
		
	} 
	if (num >= 10) 
		ft_putnbr(num / 10); 
	ft_putchar((num % 10) + '0');
}

