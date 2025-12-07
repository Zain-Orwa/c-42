#include <unistd.h>
#include <stdio.h>

int ft_is_prime(int nb){
	int i;

	if (nb <= 1)
		return (0);

	i = 2;
	while (i * i <= nb)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}
	return (1);
}

int main(){
	printf("%d\n", ft_is_prime(31));	
	printf("%d\n", ft_is_prime(90));	

	return (0);
}
