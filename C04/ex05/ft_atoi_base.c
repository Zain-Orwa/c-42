#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

/* -------------------- ft_strlen -------------------- */

int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/* -------------------- validate_base -------------------- */

int validate_base(char *base){
	int i;
	int j;
	int base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);

	i = 0;
	while (base[i])
	{
		if (base[i] == ' ' || (base[i] == '+' || base[i] == '-')
				|| (base[i] >= 9 && base[i] <= 13))
			return (0);

		j = i + 1;
		while (base[j])
		{
			if (base[i] == base[j])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/* -------------------- get_base_index -------------------- */

int get_base_index(char c, char *base){
	int i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

/* -------------------- ft_atoi_base (indexing version) -------------------- */

int ft_atoi_base(char *str, char *base){
	int i;
	int sign;
	int result;
	int base_len;
	int digit_value;

	if (!validate_base(base))
		return (0);

	i = 0;
	sign = 1;
	result = 0;
	base_len = ft_strlen(base);

	while (str[i] == ' ' || (str[i] >= 9 && str[i] <= 13))
		i++;

	while (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign = -sign;
		i++;
	}


	/*convert digit*/
	while (str[i] != '\0')
	{
		digit_value = get_base_index(str[i], base);
		if (digit_value == -1)
			break;
		result = result * base_len + digit_value;
		i++;
	}

	return (result * sign);
}

/* -------------------- MAIN (test all cases) -------------------- */

int	main(void)
{
	printf("\n===== Testing ft_atoi_base =====\n\n");

	/* 1. Decimal */
	printf("1. Decimal (\"42\"):              %d\n",
		ft_atoi_base("   ---+--+42", "0123456789"));

	/* 2. Binary */
	printf("2. Binary (\"101010\"):           %d\n",
		ft_atoi_base("   +++101010", "01"));

	/* 3. Hexadecimal */
	printf("3. Hex (\"2A\"):                  %d\n",
		ft_atoi_base("   2A", "0123456789ABCDEF"));

	/* 4. Octal */
	printf("4. Octal (\"52\"):                %d\n",
		ft_atoi_base("   52", "01234567"));

	/* 5. Custom base (poneyvif) */
	printf("5. Poneyvif (\"vn\"):             %d\n",
		ft_atoi_base("   vn", "poneyvif"));

	/* 6. Negative number */
	printf("6. Negative Hex (\"-2A\"):        %d\n",
		ft_atoi_base("   -2A", "0123456789ABCDEF"));

	/* 7. Zero */
	printf("7. Zero (\"0\"):                  %d\n",
		ft_atoi_base("0", "0123456789"));

	/* 8. Stops at invalid char */
	printf("8. Stops at invalid: \"2AZZZ\" →  %d\n",
		ft_atoi_base("2AZZZ", "0123456789ABCDEF"));

	/* 9. Invalid bases */
	printf("9. Invalid base (empty):         %d\n",
		ft_atoi_base("42", ""));
	printf("10. Invalid base (size 1):       %d\n",
		ft_atoi_base("42", "0"));
	printf("11. Invalid base (duplicate):     %d\n",
		ft_atoi_base("42", "00123456789"));
	printf("12. Invalid base (contains +):    %d\n",
		ft_atoi_base("42", "012+456789"));
	printf("13. Invalid base (contains space):%d\n",
		ft_atoi_base("42", "01 2345"));

	printf("\n===== DONE =====\n\n");
	return (0);
}

