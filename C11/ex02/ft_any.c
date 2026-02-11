#include <unistd.h>

int	ft_any(char **tab, int (*f)(char *))
{
	if (!tab || !f)
		return (0);

	while (*tab)
	{
		if (f(*tab) != 0)
			return (1);
		
		tab++;
	}

	return (0);
}

int	has_letter_z(char *str)
{
	int i = 0;
	while (str[i])
	{
		if (str[i] == 'Z')
			return (1);
		i++;
	}
	return (0);
}

int	main(void)
{
	char *strs[] = {"Hello", "World", "From", "Zebra", NULL};
	char *strs_no_z[] = {"Apple", "Banana", "Cherry", NULL};

	if (ft_any(strs, &has_letter_z))
		write(1, "Test 1: Found a 'Z'!\n", 21);
	else
		write(1, "Test 1: No 'Z' found.\n", 22);

	if (ft_any(strs_no_z, &has_letter_z))
		write(1, "Test 2: Found a 'Z'!\n", 21);
	else
		write(1, "Test 2: No 'Z' found.\n", 22);

	return (0);
}

