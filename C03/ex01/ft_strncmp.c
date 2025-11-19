#include <stdio.h>
#include <unistd.h>

int ft_strncmp(char *s1, char *s2, unsigned int n){
	while (n && *s1 && *s1 == *s2)
	{
		s1++;
		s2++;
		n--;
	}
	if (n == 0)
		return (0);
	
	return ((unsigned char)*s1 - (unsigned char)*s2);
}


/* 
 int ft_strncmp(char *s1, char *s2, unsigned int n){
 	unsigned int i;

		i= 0;
		while(i < n && s1[i] && s2[i] && s1[i] == s2[i])
		i++;
		
		if (i == n)
			return (0);
		
		return ((unsigned char)s1[i] - (unsigned char)s2[i]);	
 }
*/


int	main(void)
{
	char s1[] = "Hello World!";
	char s2[] = "Hello 42!";
	char s3[] = "Hello World!";

	printf("Test 1 (same first 5 chars):      %d\n",
		ft_strncmp(s1, s2, 5));       // 0
	printf("Test 2 (different at pos 7):      %d\n",
		ft_strncmp(s1, s2, 7));       // > 0 ('W' > '4')
	printf("Test 3 (full equal):              %d\n",
		ft_strncmp(s1, s3, 20));      // 0
	printf("Test 4 (\"abc\" vs \"abd\", n=3):   %d\n",
		ft_strncmp("abc", "abd", 3)); // < 0
	printf("Test 5 (\"abc\" vs \"abd\", n=2):   %d\n",
		ft_strncmp("abc", "abd", 2)); // 0
	printf("Test 6 (\"abc\" vs \"abcde\", n=5): %d\n",
		ft_strncmp("abc", "abcde", 5));// < 0 ('\\0' - 'd')
	printf("Test 7 (\"abcde\" vs \"abc\", n=5): %d\n",
		ft_strncmp("abcde", "abc", 5));// > 0 ('d' - '\\0')
	printf("Test 8 (n = 0):                   %d\n",
		ft_strncmp("abc", "xyz", 0));  // 0

	return (0);
}

