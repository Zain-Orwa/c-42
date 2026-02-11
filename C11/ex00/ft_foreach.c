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

void ft_foreach(int *tab, int length, void(*f)(int))
{
    int i;
    
    i = 0;
    while (i < length)
    {
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

