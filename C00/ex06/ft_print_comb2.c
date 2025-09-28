#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}


void ft_print_comb2(void){
	short first_number;
	short second_number;

	first_number = 0;
	while (first_number <= 99){
		second_number = first_number + 1;
		while (second_number <= 99){

			ft_putchar(first_number / 10 + '0');
			ft_putchar(first_number % 10 + '0');
			ft_putchar(' ');
			ft_putchar(second_number / 10 + '0');
			ft_putchar(second_number % 10 + '0');

			if (!(first_number == 98 && second_number == 99)){
				write(1, ", ", 2);
			}
			second_number++;
		}
		first_number++;	
	}
}

int main(){
	ft_print_comb2();
	return (0);
}
