#include <stdio.h>
#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_putstr_non_printable(char *str){
	int  i;
	char *hex_digit;
	unsigned char c;

	hex_digit = "0123456789abcdef";
	i = 0;

	while (str[i]){
		
		if (str[i] >= 32 && str[i] <= 126)
		{
			ft_putchar(str[i]);
		}
		else
		{
			c = (unsigned char)str[i];
			ft_putchar('\\');
			ft_putchar(hex_digit[c / 16]);
			ft_putchar(hex_digit[c % 16]);
		}
		i++;
	}
}

int main(){
	char *str = "Coucou\ntu vas bien ?";

	ft_putstr_non_printable(str);


	return (0);
}
