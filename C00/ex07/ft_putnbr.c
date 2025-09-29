#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_putnbr(int nb){

	long  num;

	num = nb;

	if (num < 0){
		ft_putchar('-');
		num = -num;
	}

	if (num >= 10)
		ft_putnbr(num / 10);

	ft_putchar('0' + (num % 10));

}

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


