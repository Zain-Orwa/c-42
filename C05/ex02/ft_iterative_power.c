#include <stdio.h>
#include <unistd.h>

int ft_iterative_power(int nb, int power){
	int result;

	if (power < 0) return (0);
	if (power == 0)	return (1);

	result = 1;
	while (power > 0)
	{
		result *= nb;
		power--;
	}

	return (result);
}

int main(void){
    printf("2^4  = %d\n", ft_iterative_power(2, 4));   // 16
    printf("5^0  = %d\n", ft_iterative_power(5, 0));   // 1
    printf("0^0  = %d\n", ft_iterative_power(0, 0));   // 1 (by subject)
    printf("3^-2 = %d\n", ft_iterative_power(3, -2));  // 0 (by subject)
    return 0;
}
