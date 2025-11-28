#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

int ft_strlen(char *str){
	int  i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int validate_base(char *base){
	int i;
	int j;
	int base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);

	i = 0;
	while (base[i] != '\0')
	{
		if (base[i] == '+' || base[i] == '-')
			return (0);

		j = i + 1;
		while (base[j] != '\0')
		{
			if (base[i] == base[j])
				return (0);
			j++;	
		}
		i++;
	}
	return (1);
}

void ft_putnbr_base(int nbr, char *base){
	int  base_len;
	long long_nbr;

	if (!validate_base(base))
		return;

	long_nbr = nbr;
	if (long_nbr < 0){
		ft_putchar('-');
		long_nbr = -long_nbr;
	}

	base_len = ft_strlen(base);
	if (long_nbr >= base_len)
		ft_putnbr_base(long_nbr / base_len, base);
	ft_putchar(base[long_nbr % base_len]);
}

int main(void)
{
    printf("Testing ft_putnbr_base:\n\n");

    // Test 1: Decimal (base 10)
    printf("1. Decimal (base 10): ");
    ft_putnbr_base(42, "0123456789");
    printf("\n");

    // Test 2: Binary (base 2)
    printf("2. Binary (base 2): ");
    ft_putnbr_base(42, "01");
    printf("\n");

    // Test 3: Hexadecimal (base 16)
    printf("3. Hexadecimal (base 16): ");
    ft_putnbr_base(42, "0123456789ABCDEF");
    printf("\n");

    // Test 4: Octal (base 8)
    printf("4. Octal (base 8): ");
    ft_putnbr_base(42, "01234567");
    printf("\n");

    // Test 5: Negative numbers
    printf("5. Negative decimal: ");
    ft_putnbr_base(-42, "0123456789");
    printf("\n");

    // Test 6: Zero
    printf("6. Zero: ");
    ft_putnbr_base(0, "0123456789");
    printf("\n");

    // Test 7: Custom base (poneyvif)
    printf("7. Custom base (poneyvif): ");
    ft_putnbr_base(42, "poneyvif");
    printf("\n");

    // Test 8: Edge case (INT_MAX)
    printf("8. INT_MAX: ");
    ft_putnbr_base(2147483647, "0123456789");
    printf("\n");

    // Test 9: Edge case (INT_MIN)
    printf("9. INT_MIN: ");
    ft_putnbr_base(-2147483648, "0123456789");
    printf("\n");

    // Test 10: Invalid bases (should print nothing)
    printf("10. Invalid base (empty): ");
    ft_putnbr_base(42, "");
    printf("(nothing above this line)\n");

    printf("11. Invalid base (size 1): ");
    ft_putnbr_base(42, "0");
    printf("(nothing above this line)\n");

    printf("12. Invalid base (duplicates): ");
    ft_putnbr_base(42, "01234567890");
    printf("(nothing above this line)\n");

    printf("13. Invalid base (contains +): ");
    ft_putnbr_base(42, "012+456789");
    printf("(nothing above this line)\n");

    printf("14. Invalid base (contains -): ");
    ft_putnbr_base(42, "01234567-9");
    printf("(nothing above this line)\n");

    return 0;
}
