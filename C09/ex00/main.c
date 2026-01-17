#include <unistd.h>

void	ft_putchar(char c);
void	ft_putstr(char *str);
void	ft_swap(int *a, int *b);
int		ft_strlen(char *str);
int		ft_strcmp(char *s1, char *s2);

int	main(void)
{
	int		a = 10;
	int		b = 20;
	char	str[] = "Hello 42!";
	int		len;

	ft_putstr("Before swap: ");
	ft_putchar('\n');
	ft_putstr("a = ");
	/* very primitive int print just for test */
	ft_putchar(a / 10 + '0');
	ft_putchar(a % 10 + '0');
	ft_putchar('\n');

	ft_putstr("b = ");
	ft_putchar(b / 10 + '0');
	ft_putchar(b % 10 + '0');
	ft_putchar('\n');

	ft_swap(&a, &b);

	ft_putstr("After swap: ");
	ft_putchar('\n');
	ft_putstr("a = ");
	ft_putchar(a / 10 + '0');
	ft_putchar(a % 10 + '0');
	ft_putchar('\n');

	ft_putstr("String: ");
	ft_putstr(str);
	ft_putchar('\n');

	len = ft_strlen(str);
	ft_putstr("Length: ");
	ft_putchar(len / 10 + '0');
	ft_putchar(len % 10 + '0');
	ft_putchar('\n');

	return (0);
}

