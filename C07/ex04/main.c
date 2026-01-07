/* main.c */
#include <stdio.h>
#include <stdlib.h>

char	*ft_convert_base(char *nbr, char *base_from, char *base_to);

int	main(void)
{
	char	*result;

	printf("=== Basic Tests ===\n\n");

	/* Test 1: Decimal to Binary */
	result = ft_convert_base("42", "0123456789", "01");
	printf("42 (decimal) -> binary: %s\n", result);
	if (result)
		free(result);

	/* Test 2: Hexadecimal to Decimal */
	result = ft_convert_base("FF", "0123456789ABCDEF", "0123456789");
	printf("FF (hex) -> decimal: %s\n", result);
	if (result)
		free(result);

	/* Test 3: Negative number */
	result = ft_convert_base("-42", "0123456789", "01");
	printf("-42 (decimal) -> binary: %s\n", result);
	if (result)
		free(result);

	/* Test 4: Zero */
	result = ft_convert_base("0", "0123456789", "0123456789ABCDEF");
	printf("0 (decimal) -> hex: %s\n", result);
	if (result)
		free(result);

	/* Test 5: Binary to Octal */
	result = ft_convert_base("101010", "01", "01234567");
	printf("101010 (binary) -> octal: %s\n", result);
	if (result)
		free(result);

	/* Test 6: Invalid base */
	result = ft_convert_base("42", "0123456789", "01+");
	printf("Invalid base test: %s (should be NULL)\n", result);
	if (result)
		free(result);

	/* Test 7: INT_MAX */
	result = ft_convert_base("2147483647", "0123456789", "01");
	printf("INT_MAX -> binary: %s\n", result);
	if (result)
		free(result);

	/* Test 8: INT_MIN */
	result = ft_convert_base("-2147483648", "0123456789", "01");
	printf("INT_MIN -> binary: %s\n", result);
	if (result)
		free(result);

	return (0);
}
