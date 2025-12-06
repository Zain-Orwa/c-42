#include <unistd.h>
#include <stdio.h>

int ft_sqrt(int nb){
	int i;
	
	if (nb <= 0)
		return (0);

	i = 0;
	while (i <= 46340 && i * i <= nb)
	{
		if (i * i == nb)
			return (i);

		i++;
	}
	return (0);
}

int main(void)
{
    printf("ft_sqrt(0) = %d\n", ft_sqrt(0));
    printf("ft_sqrt(1) = %d\n", ft_sqrt(1));
    printf("ft_sqrt(4) = %d\n", ft_sqrt(4));
    printf("ft_sqrt(9) = %d\n", ft_sqrt(9));
    printf("ft_sqrt(25) = %d\n", ft_sqrt(25));
    printf("ft_sqrt(8) = %d\n", ft_sqrt(8));    // Not a perfect square
    printf("ft_sqrt(-4) = %d\n", ft_sqrt(-4));  // Negative number
    printf("ft_sqrt(100) = %d\n", ft_sqrt(100));
    printf("ft_sqrt(121) = %d\n", ft_sqrt(121));
    
    return 0;
}

