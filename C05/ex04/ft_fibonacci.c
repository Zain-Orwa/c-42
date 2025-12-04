#include <unistd.h>
#include <stdio.h>

int ft_fibonacci(int index){
	int prev1;
	int prev2;
	int Fibon;

	if (index < 0) return (-1);
	if (index == 0) return (0);
	if (index == 1) return (1);

	prev1 = 0;
	prev2 = 1;
	Fibon = 0;
	if (index >= 2)
	{
		Fibon = prev1 + prev2;
		prev2 = prev1;
		prev1 = Fibon;
		ft_fibonacci(index - 1);	
	}

	return (Fibon);
}

int	main(void)
{
	printf("Index 0: %d\n", ft_fibonacci(0));   // Expected: 0
	printf("Index 1: %d\n", ft_fibonacci(1));   // Expected: 1
	printf("Index 2: %d\n", ft_fibonacci(2));   // Expected: 1
	printf("Index 3: %d\n", ft_fibonacci(3));   // Expected: 2
	printf("Index 4: %d\n", ft_fibonacci(4));   // Expected: 3
	printf("Index 5: %d\n", ft_fibonacci(5));   // Expected: 5
	printf("Index 6: %d\n", ft_fibonacci(6));   // Expected: 8
	printf("Index 7: %d\n", ft_fibonacci(7));   // Expected: 13
	printf("Index 8: %d\n", ft_fibonacci(8));   // Expected: 21
	printf("Index 9: %d\n", ft_fibonacci(9));   // Expected: 34

	// Test edge cases
	printf("Index -1: %d\n", ft_fibonacci(-1)); // Expected: -1
	printf("Index -5: %d\n", ft_fibonacci(-5)); // Expected: -1

	return (0);
}
