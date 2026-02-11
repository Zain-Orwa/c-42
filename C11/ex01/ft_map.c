#include <stdlib.h>
#include <unistd.h>

int	*ft_map(int *tab, int length, int (*f)(int))
{
	int	i;
	int	*result;

	if (!tab || !f || length <= 0)
		return (NULL);
	result = (int *)malloc(sizeof(int) * length);
	if (!result)
		return (NULL);
	i = 0;
	while (i < length)
	{
		result[i] = f(tab[i]);
		i++;
	}
	return (result);
}

/* ========================================================================== */
/* TEST SECTION                                                               */
/* ========================================================================== */

int	double_it(int n)
{
	return (n * 2);
}

/* Helper function - prints a single character */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/* ========================================================================== */
/* VERSION 1: SIMPLE RECURSIVE ft_putnbr (RECOMMENDED FOR PISCINE)           */
/* ========================================================================== */

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
	if (nb < 0)
	{
		ft_putchar('-');
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	ft_putchar((nb % 10) + '0');
}

/* ========================================================================== */
/* VERSION 2: OPTIMIZED ft_putnbr WITH BUFFER (REFERENCE ONLY)               */
/* ========================================================================== */

/*
#include <stdbool.h>

void	ft_putnbr_buffer(int n)
{
	long	nb;
	char	buffer[12];
	int		i;
	bool	is_negative;

	nb = n;
	is_negative = (nb < 0);
	if (is_negative)
		nb = -nb;
	if (nb == 0)
	{
		ft_putchar('0');
		return ;
	}
	i = 11;
	buffer[i] = '\0';
	while (nb > 0)
	{
		i--;
		buffer[i] = (nb % 10) + '0';
		nb /= 10;
	}
	if (is_negative)
	{
		i--;
		buffer[i] = '-';
	}
	write(1, &buffer[i], 11 - i);
}
*/

/* ========================================================================== */
/* MAIN FUNCTION - Tests ft_map with ft_putnbr                               */
/* ========================================================================== */

int	main(void)
{
	int	array[] = {1, 2, 3, 4, 5};
	int	*new_array;
	int	i;
	int	length;

	length = 5;
	new_array = ft_map(array, length, &double_it);
	if (new_array)
	{
		i = 0;
		while (i < length)
		{
			ft_putnbr(new_array[i]);
			ft_putchar(' ');
			i++;
		}
		ft_putchar('\n');
		free(new_array);
		new_array = NULL;
	}
	return (0);
}


