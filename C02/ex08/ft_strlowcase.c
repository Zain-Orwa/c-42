#include <unistd.h>
#include <stdio.h>

char *ft_strlowcase(char *str)
{
	int i = 0;
	while (str[i] != '\0')
	{
		if (str[i] >= 'A' && str[i] <= 'Z')
			str[i] += 32;
		i++;
	}
	return (str);
}

int main(void)
{
	char str1[] = "HELLO WORLD!";
	char str2[] = "already lower";
	char str3[] = "42SCHOOL";

	printf("Before: %-15s\n", str1);
	ft_strlowcase(str1);
	printf("After : %-15s\n\n", str1);

	printf("Before: %-15s\n", str2);
	ft_strlowcase(str2);
	printf("After : %-15s\n\n", str2);

	printf("Before: %-15s\n", str3);
	ft_strlowcase(str3);
	printf("After : %-15s\n", str3);

	return (0);
}

