/* ft_convert_base2.c */
#include <stdlib.h>

/* Helper functions */

/*----------------- ft_strlen ----------------*/
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*--------------- validate_base -------------*/
int	validate_base(char *base)
{
	int	i;
	int	j;
	int	base_len;

	base_len = ft_strlen(base);
	if (base_len <= 1)
		return (0);

	i = 0;
	while (base[i])
	{
		/* FIXED: base[i] <= 32 includes space (32) so we don't need separate check */
		if (base[i] <= 32 || base[i] == 127 || base[i] == '+' || base[i] == '-')
			return (0);

		j = i + 1;
		while (base[j])
		{
			if (base[j] == base[i])
				return (0);
			j++;
		}
		i++;
	}
	return (1);
}

/*--------------- get_base_index ---------------*/
int	get_base_index(char c, char *base)
{
	int	i;

	i = 0;
	while (base[i])
	{
		if (c == base[i])
			return (i);
		i++;
	}
	return (-1);
}

/*------------- ft_atoi_base ------------------*/
int	ft_atoi_base(char *str, char *base)
{
	int			  i;
	int			  sign;
	long long	result;
	int			  base_len;
	int			  digit_value;

	/* FIXED: Added NULL check for str */
	if (!str || !validate_base(base))
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

	while (str[i])
	{
		digit_value = get_base_index(str[i], base);
		if (digit_value == -1)
			break ;

		result = result * base_len + digit_value;

		if ((sign == 1 && result > 2147483647) || (sign == -1 && result > 2147483648))
			return (0);
		i++;
	}
	return ((int)result * sign);
}

/*-------------- count_digit_in_base --------------*/
int	count_digit_in_base(long num, int base_len)
{
	int	count;

	if (num == 0)
		return (1);

	if (num < 0)
		num = -num;

	count = 0;
	while (num > 0)
	{
		num = num / base_len;
		count++;
	}
	return (count);
}

/*----------------- ft_itoa_base ----------------*/
char	*ft_itoa_base(int nbr, char *base)
{
	int		i;
	long	num;
	int		base_len;
	int		total_len;
	char	*result;

	/* FIXED: Added NULL check for base */
	if (!validate_base(base))
		return (NULL);

	num = (long)nbr;
	if (num == 0)
	{
		result = (char *)malloc(sizeof(char) * 2);
		if (!result)
			return (NULL);
		result[0] = base[0];
		result[1] = '\0';
		return (result);
	}

	base_len = ft_strlen(base);
	total_len = count_digit_in_base(num, base_len);
	if (num < 0)
		total_len++;

	result = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!result)
		return (NULL);
	result[total_len] = '\0';
	if (num < 0)
	{
		result[0] = '-';
		num = -num;
	}

	i = total_len - 1;
	while (num > 0)
	{
		result[i] = base[num % base_len];
		num = num / base_len;
		i--;
	}
	return (result);
}

