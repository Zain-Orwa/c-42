#include <unistd.h>
#include <stdio.h>

int ft_is_prime(int nb){
	int i;

	if (nb <= 1)
		return (0);

	i = 2;
	while (i <= nb / i)
	{
		if (nb % i == 0)
			return (0);
		i++;
	}

	return (1);
}

int ft_find_next_prime(int nb){
	if (nb <= 2)
		return (2);

	while (!ft_is_prime(nb))
		nb++;

	return (nb);
}

int	main(void)
{
	printf("Next prime of -3 is: %d\n", ft_find_next_prime(-3));
	printf("Next prime of 6  is: %d\n", ft_find_next_prime(6));
	printf("Next prime of 13 is: %d\n", ft_find_next_prime(13));
	printf("Next prime of 25 is: %d\n", ft_find_next_prime(25));
	printf("Next prime of 84 is: %d\n", ft_find_next_prime(84));

	return (0);
}
