#include <unistd.h>

static void ft_putchar(char character){
	write(1, &character, 1);
}

static void print_combination(char first_digit, char second_digit, char third_digit){
	ft_putchar(first_digit);
	ft_putchar(second_digit);
	ft_putchar(third_digit);
	if (!(first_digit == '7' && second_digit == '8' && third_digit == '9')){
		write(1, ", ", 2);
	}
}

void ft_print_comb(void){

	int first_digit = '0';
	while (first_digit <= '7'){

		int second_digit = first_digit + 1;
		while (second_digit <= '8'){

			int third_digit = second_digit + 1;
			while (third_digit <= '9'){
				print_combination(first_digit, second_digit, third_digit);

				third_digit++;
				}
			second_digit++;
			}
		first_digit++;
		}
}

int main(){
	ft_print_comb();
	return (0);
}
