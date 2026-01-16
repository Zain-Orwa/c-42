#include <unistd.h>
#include <stdlib.h>
#include "ft_stock_str.h"

/* ============================== */
/*            OUTPUT              */
/* ============================== */

/* Write a single character using write() */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/* Print a C-string (defensive: ignore NULL) */
void	ft_putstr(char *str)
{
	if (!str)
		return;
	while (*str)
		write(1, str++, 1);
}

/*
** Print an integer in decimal using recursion.
** - We promote to long to safely handle INT_MIN.
*/
void	ft_putnbr(int nbr)
{
	long	num;

	num = nbr;
	if (num < 0)
	{
		ft_putchar('-');
		num = -num;
	}
	if (num >= 10)
		ft_putnbr(num / 10);
	ft_putchar((num % 10) + '0');
}

/*
** Display the content of a t_stock_str array created by ft_strs_to_tab.
** For each element (until sentinel where str == 0):
**   - print str  followed by '\n'
**   - print size followed by '\n'
**   - print copy followed by '\n'
*/
void	ft_show_tab(struct s_stock_str *par)
{
	int	i;

	if (!par)
		return;
	i = 0;
	while (par[i].str)           /* sentinel: last element has str == 0 */
	{
		ft_putstr(par[i].str);
		ft_putchar('\n');
		ft_putnbr(par[i].size);
		ft_putchar('\n');
		ft_putstr(par[i].copy);
		ft_putchar('\n');
		i++;
	}
}

/* ============================== */
/*        STRING UTILITIES        */
/* ============================== */

/* Return length of a C-string (no NULL check here, caller ensures it). */
int	ft_strlen(char *str)
{
	int	len;

	len = 0;
	while (str[len])
		len++;
	return (len);
}

/*
** Duplicate a string on the heap.
** - returns a new malloc'ed buffer with same contents as src
** - returns NULL on error (or if src itself is NULL)
*/
char	*ft_strdup(char *src)
{
	int		i;
	int		len;
	char	*dst;

	if (!src)
		return (NULL);
	len = ft_strlen(src);
	dst = (char *)malloc(sizeof(char) * (len + 1));
	if (!dst)
		return (NULL);
	i = 0;
	while (i < len)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* ============================== */
/*    BUILD ARRAY OF STRUCTS      */
/* ============================== */

/*
** Convert an array of strings (ac, av) into an array of t_stock_str.
**
** For each i in [0, ac):
**   arr[i].size = length of av[i]
**   arr[i].str  = av[i]          (pointer to original string)
**   arr[i].copy = ft_strdup(av[i]) (heap-allocated copy)
**
** The array itself is allocated on the heap with ac + 1 elements.
** The last element is a sentinel:
**   arr[ac].str = 0
**   arr[ac].size = 0
**   arr[ac].copy = 0
**
** On any allocation failure, all previously allocated copies
** and the array are freed, and NULL is returned.
*/
t_stock_str	*ft_strs_to_tab(int ac, char **av)
{
	int			i;
	t_stock_str	*arr;

	if (!av || ac < 0)
		return (NULL);
	arr = (t_stock_str *)malloc(sizeof(t_stock_str) * (ac + 1));
	if (!arr)
		return (NULL);
	i = 0;
	while (i < ac)
	{
		arr[i].size = ft_strlen(av[i]);
		arr[i].str = av[i];
		arr[i].copy = ft_strdup(av[i]);
		if (!arr[i].copy)
		{
			while (--i >= 0)
				free(arr[i].copy);
			free(arr);
			return (NULL);
		}
		i++;
	}
	arr[i].size = 0;
	arr[i].str = 0;
	arr[i].copy = 0;
	return (arr);
}

/* ============================== */
/*              MAIN              */
/* ============================== */
/*
** Test main (not part of the official 42 submission).
** - Builds the t_stock_str array from argc/argv
** - Prints it with ft_show_tab
** - Frees the allocated memory afterwards (good practice)
*/
int	main(int argc, char **argv)
{
	t_stock_str	*arr;
	int			i;

	arr = ft_strs_to_tab(argc, argv);
	if (!arr)
		return (1);
	ft_show_tab(arr);
	/* free all copies and the struct array */
	i = 0;
	while (arr[i].str)
	{
		free(arr[i].copy);
		i++;
	}
	free(arr);
	return (0);
}

