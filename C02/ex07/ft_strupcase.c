#include <unistd.h>
#include <stdio.h>

char	*ft_strupcase(char *str)
{
	int	i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'z')
			str[i] -= 32; // convert lowercase to uppercase
		i++;
	}
	return (str);
}

int	main(void)
{
	char str1[] = "hello world!";
	char str2[] = "Already UPPER";
	char str3[] = "42school";

	printf("Before: %-15s | After: %s\n", str1, ft_strupcase(str1));
	printf("Before: %-15s | After: %s\n", str2, ft_strupcase(str2));
	printf("Before: %-15s | After: %s\n", str3, ft_strupcase(str3));

	return (0);
}

