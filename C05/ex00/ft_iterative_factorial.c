#include <unistd.h>
#include <stdio.h>

int ft_iterative_factorial(int nb){
	int i;
	int fact;

	if (nb < 0)
		return (0);

	if (nb == 0)
		return (1);

	i = 1;
	fact = 1;
	while (i <= nb){
		fact *= i;
		i++;
	}
	return (fact);
}

/*int ft_iterative_factorial(int nb){
	int i;
	int fact;

	if (nb < 0)
		return (0);

	if (nb == 0)
		return (1);

	i = nb;
	fact = 1;
	while (i >= 1){
		fact *= i;
		i--;
	}
	return (fact);
}*/



int main(){
	int nb = 4;
	printf("%d\n", ft_iterative_factorial(nb));

	return (0);
}
