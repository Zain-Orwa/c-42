#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void print_combination(int digits[], int n){

	int  i;

	i = 0;
	while (i < n)
	{
		ft_putchar(digits[i] + '0');
		i++;
	}
}

int  is_last_combination(int digits[], int n){

	int  i;

	i = 0;
	while (i < n)
	{
			if (digits[i] != 9 - (n - 1 - i))
			{
				return (0);
			}
			i++;
	}
	
	return (1);
}

void  increment_combination(int digits[], int n){

	int   i;
	int   max;

	i = n - 1;
	while (i >= 0)
	{
			max = 9 - (n - 1 - i);

			if (digits[i] < max)
			{
				digits[i]++;

				while (++i < n) // reset //
				{
					digits[i] = digits[i - 1] + 1; 
				}
				
				return;
			}
		i--;
	}
}


void   ft_print_combn(int n){
	int digits[10];
	int i;

	i = 0;
	while (i < n){
		digits[i] = i;
		i++;
	}

	while (1){
			print_combination(digits, n);

			if (is_last_combination(digits, n))
				return;

			ft_putchar(',');
			ft_putchar(' ');
			
			increment_combination(digits, n);
	}
}

int main(){
	ft_print_combn(2);

	return (0);
}

