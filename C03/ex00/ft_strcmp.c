#include <unistd.h>
#include <stdio.h>

int ft_strcmp(char *s1, char *s2){
	while (*s1 && *s1 == *s2){
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int main()
{
	char str1[] = "Hello World!";
	char str2[] = "Hello World!";

	printf("%d\n", ft_strcmp(str1, str2));

	return 0;
}
