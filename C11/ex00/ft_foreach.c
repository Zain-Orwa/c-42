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
    int array[] = {42, -123, 0, 789, 2147483647, -2147483648};
    int size = sizeof(array) / sizeof(array[0]);

    ft_putchar('[');
    ft_foreach(array, size, &ft_putnbr);
    ft_putchar(']');
    ft_putchar('\n');

    return (0);
}
