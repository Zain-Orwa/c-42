/* ft_utils.c */
#include "ft_tail.h"

size_t	ft_strlen(const char *str)
{
	const char	*start;

	start = str;
	while (*str)
		str++;
	return ((size_t)(str - start));
}

int	ft_strcmp(char *s1, char *s2)
{
	while (*s1 && *s2 && *s1 == *s2)
	{
		s1++;
		s2++;
	}
	return ((unsigned char)*s1 - (unsigned char)*s2);
}

int	ft_atoi(char *str)
{
	int	result;

	result = 0;
	while (*str)
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	return (result);
}

void	ft_putstr(const char *str)
{
	write(1, str, ft_strlen(str));
}

