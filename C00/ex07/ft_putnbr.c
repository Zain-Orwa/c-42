#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_putnbr(int nb){

	long  num;

	num = nb;

	if (num < 0){
		ft_putchar('-');
		num *= -1;
	}

	if (num >= 10)
		ft_putnbr(num / 10);

	ft_putchar((num % 10) + '0');
}

/*
 * buffer version:
 *
 void	ft_putnbr(int n)
{
	long	nb;
	char	buffer[12];  // Enough for INT_MIN + sign + null
	int		i;
	bool	is_negative;

	nb = n;
	is_negative = (nb < 0);
	if (is_negative)
		nb = -nb;
	
	// Handle zero case
	if (nb == 0)
	{
		ft_putchar('0');
		return;
	}
	
	// Fill buffer from right to left
	i = 11;
	buffer[i] = '\0';
	while (nb > 0)
	{
		i--;
		buffer[i] = (nb % 10) + '0';
		nb /= 10;
	}
	
	// Add sign if negative
	if (is_negative)
	{
		i--;
		buffer[i] = '-';
	}
	
	// Write the entire number at once
	write(1, &buffer[i], 11 - i);
}
*/

int main(void){

	write(1, "Print a positive number: ", 26);
	ft_putnbr(42);
	write(1, "\nPrint a negative number: ", 26);
	ft_putnbr(-42);
	write(1, "\nPrint zero: ", 13);
	ft_putnbr(0);
	write(1, "\nPrint the max value of int: ", 29);
	ft_putnbr(2147483647);
	write(1, "\nPrint the min value of int: ", 29);
	ft_putnbr(-2147483648);
	write(1, "\n", 1);

	return (0);
}


