#include <unistd.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void ft_print_comb(void){

	int digi1 = '0';
	while (digi1 <= '7'){
		int digi2 = digi1 + 1;
		while (digi2 <= '8'){
			int digi3 = digi2 + 1;
			while (digi3 <= '9'){
				ft_putchar(digi1);
				ft_putchar(digi2);
				ft_putchar(digi3);
				
				if (digi1 != '7' || digi2 != '8' || digi3 != '9'){
					ft_putchar(',');
					ft_putchar(' ');
				}

				digi3++;
			}
			digi2++;
		}
		digi1++;
	}
}

int main(){
	ft_print_comb();
	return (0);
}
