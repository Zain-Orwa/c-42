#include <unistd.h>

void ft_putchar(char c)
{
    write(1, &c, 1);
}

void ft_putnbr(int nb)
{
    if (nb == -2147483648)
    {
        write(1, "-2147483648", 11);
        return;
    }
    if (nb < 0)
    {
        ft_putchar('-');
        nb = -nb;
    }
    if (nb >= 10)
    {
        ft_putnbr(nb / 10);
        ft_putnbr(nb % 10);
    }
    else
        ft_putchar(nb + '0');
}

void ft_putnbr_space(int nb)
{
    ft_putnbr(nb);
    ft_putchar(' ');
}

void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	// Safety check: Don't do anything if the pointers are NULL or length is invalid
	if (!tab || !f || length <= 0)
		return ;

	i = 0;
	while (i < length)
	{
		// Execute the function 'f' using the value at the current index
		f(tab[i]);
		i++;
	}
}

int main(void)
{
    int array1[] = {1, 2, 3, 4, 5};
    int array2[] = {-10, -20, -30};
    int array3[] = {0};
    
    // Test 1: Print numbers without separator
    ft_foreach(array1, 5, &ft_putnbr);
    ft_putchar('\n');
    
    // Test 2: Print numbers with space separator
    ft_foreach(array2, 3, &ft_putnbr_space);
    ft_putchar('\n');
    
    // Test 3: Single element array
    ft_foreach(array3, 1, &ft_putnbr);
    ft_putchar('\n');
    
    return (0);
}

/*
#include <unistd.h>


void	ft_foreach(int *tab, int length, void (*f)(int))
{
	int	i;

	// Safety check: Don't do anything if the pointers are NULL or length is invalid
	if (!tab || !f || length <= 0)
		return ;

	i = 0;
	while (i < length)
	{
		// Execute the function 'f' using the value at the current index
		f(tab[i]);
		i++;
	}
}



// A simple function to print an integer using write
void	ft_putnbr(int n)
{
	long	nb;
	char	c;

	nb = n;
	if (nb < 0)
	{
		write(1, "-", 1);
		nb = -nb;
	}
	if (nb > 9)
		ft_putnbr(nb / 10);
	c = (nb % 10) + '0';
	write(1, &c, 1);
}

// A wrapper to print the number followed by a space for readability
void	print_item(int n)
{
	ft_putnbr(n);
	write(1, " ", 1);
}

int	main(void)
{
	int		my_array[] = {42, 1337, 7, -5, 0, 100};
	int		size = 6;

	write(1, "Array contents: ", 16);

	// Calling the exercise function with our array and our print function
	ft_foreach(my_array, size, &print_item);

	write(1, "\nTest Complete.\n", 16);
	return (0);
}
*/
