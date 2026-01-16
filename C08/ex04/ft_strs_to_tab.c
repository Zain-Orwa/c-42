#include <stdio.h>
#include <stdlib.h>
#include "ft_stock_str.h"

int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;	
	return (len);
}

char *ft_strdup(char *src){
	int i;
	int len;
	char *dst;

	if (!src)
		return (NULL);

	len = ft_strlen(src);
	dst = (char*)malloc(sizeof(char) * (len + 1));
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

t_stock_str *ft_strs_to_tab(int ac, char **av){
	int i;
	t_stock_str *arr;

	if (!av || ac < 0)
		return (NULL);

	arr = (t_stock_str*)malloc(sizeof(t_stock_str) * (ac + 1));
	if (!arr)
		return (NULL);

	i = 0;
	while (i < ac)
	{
		arr[i].size = ft_strlen(av[i]);
		arr[i].str  = av[i];
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
	arr[i].str  = 0;
	arr[i].copy = 0;

	return (arr);
}

void	print_array(t_stock_str *str)
{
	int	i;

	i = 0;

	// Until reach the null the struct informations are printed
	while (str[i].str != NULL)
	{
		printf("Indice: %d - Size: %d - String: %s - Copy: %s\n",
		i, str[i].size,	str[i].str, str[i].copy);
	       i++;
	}
	free(str);
}

int	main(int argc, char **argv)
{
	print_array(ft_strs_to_tab(argc, argv));
}
