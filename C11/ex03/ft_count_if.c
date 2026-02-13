#include <unistd.h>

int	ft_count_if(char **tab, int length, int (*f)(char *))
{
	int	i;
	int	count;

	// Pointer and length guards
	if (!tab || !f || length <= 0)
		return (0);
	
	i = 0;
	count = 0;
	while (i < length)
	{
		// If the function returns anything other than 0, increment count
		if (f(tab[i]) != 0)
			count++;
		i++;
	}
	return (count);
}

/* =============================================================================
** TEST SECTION
** =============================================================================
*/

// Test function: returns 1 if string length is greater than 3
int	is_long_word(char *str)
{
	int len = 0;
	while (str[len])
		len++;
	return (len > 3);
}

int	main(void)
{
	// Array of 4 strings
	char *words[] = {"Hi", "Hello", "C", "Code"};
	int result;

	// Should count "Hello" and "Code" (Total: 2)
	result = ft_count_if(words, 4, &is_long_word);

	// Basic output logic (since we can't use printf)
	if (result == 2)
		write(1, "Test Passed: Found 2 long words.\n", 33);
	else
		write(1, "Test Failed.\n", 13);

	return (0);
}

