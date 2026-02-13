#include <stdio.h>

int	ft_is_sort(int *tab, int length, int (*f)(int, int))
{
	int	i;
	int	asc;
	int	desc;

	if (!tab || length <= 1)
		return (1);

	i = 0;
	asc = 1;
	desc = 1;
	while (i < length - 1)
	{
		if (f(tab[i], tab[i + 1]) > 0)
			asc = 0;
		else
		{
			if (f(tab[i], tab[i + 1]) < 0)
				desc = 0;
		}
		i++;
	}
	return (asc || desc);
}

int	compare(int a, int b)
{
	return (a - b);
}

int	main(void)
{
	int	tab1[] = {1, 2, 3, 4, 5};
	int	tab2[] = {5, 4, 3, 2, 1};
	int	tab3[] = {1, 2, 3, 3, 4, 5};
	int	tab4[] = {1, 3, 2, 4, 5};
	int	tab5[] = {42};
	int	tab6[] = {};

	printf("Test 1 (ascending): %d\n", ft_is_sort(tab1, 5, &compare));
	printf("Test 2 (descending): %d\n", ft_is_sort(tab2, 5, &compare));
	printf("Test 3 (with equals): %d\n", ft_is_sort(tab3, 6, &compare));
	printf("Test 4 (not sorted): %d\n", ft_is_sort(tab4, 5, &compare));
	printf("Test 5 (single): %d\n", ft_is_sort(tab5, 1, &compare));
	printf("Test 6 (empty): %d\n", ft_is_sort(tab6, 0, &compare));
	return (0);
}


/* else if is forbiden but for efficiency this is better
int ft_is_sort(int *tab, int length, int(*f)(int, int)){
	int i;
	int asc;
	int desc;

	if (!tab || length <= 0)
		return (0);

	i = 0;
	asc = 1;
	desc = 1;
	while(i < length - 1)
	{
		if (f(tab[i], tab[i + 1]) > 0)
			asc = 0;
		else if (f(tab[i], tab[i + 1]) < 0)
			desc = 0;

		i++;
	}

	return (asc || desc);
}
*/
