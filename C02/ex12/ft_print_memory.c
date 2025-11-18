#include <unistd.h>

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/* Print a single byte as two lowercase hex digits */
void	print_byte_hex(unsigned char byte)
{
	unsigned char	high_nibble;
	unsigned char	low_nibble;

	high_nibble = byte / 16;
	low_nibble = byte % 16;

	if (high_nibble < 10)
		ft_putchar('0' + high_nibble);
	else
		ft_putchar('a' + (high_nibble - 10));

	if (low_nibble < 10)
		ft_putchar('0' + low_nibble);
	else
		ft_putchar('a' + (low_nibble - 10));
}

void	print_address_hex(void *addr)
{
	unsigned char	*addr_ptr;
	int				i;

	addr_ptr = (unsigned char *)&addr;
	i = (int)(sizeof(addr) - 1);

	while (i >= 0)
	{
		print_byte_hex(addr_ptr[i]);
		i--;
	}
	ft_putchar(':');
}


void	print_16_bytes_hex(void *ptr, unsigned int size)
{
	unsigned char	*byte_ptr;
	int				bytes_to_print;
	int				i;

	byte_ptr = (unsigned char *)ptr;
	if (size < 16)
		bytes_to_print = (int)size;
	else
		bytes_to_print = 16;

	i = 0;
	while (i < 16)
	{
		if (i % 2 == 0)
			ft_putchar(' ');

		if (i < bytes_to_print)
		{
			print_byte_hex(byte_ptr[i]);
		}
		else
		{
			ft_putchar(' ');
			ft_putchar(' ');
		}
		i++;
	}
}


void	print_printable_chars(void *ptr, unsigned int size)
{
	unsigned char	*byte_ptr;
	int				chars_to_print;
	int				i;

	byte_ptr = (unsigned char *)ptr;
	if (size < 16)
		chars_to_print = (int)size;
	else
		chars_to_print = 16;

	i = 0;
	while (i < chars_to_print)
	{
		if (byte_ptr[i] >= 32 && byte_ptr[i] < 127)
			ft_putchar(byte_ptr[i]);
		else
			ft_putchar('.');
		i++;
	}
}

void	*ft_print_memory(void *addr, unsigned int size)
{
	/* Match original: if size == 1 (empty string ""), print nothing */
	if (size == 1)
		return (addr);

	print_address_hex(addr);
	print_16_bytes_hex(addr, size);
	ft_putchar(' ');
	print_printable_chars(addr, size);
	ft_putchar('\n');	
	return (addr);
}

int	main(void)
{
	char	empty[] = "";

	char	str[] = "Bonjour les amin----";
	char	str1[] = "ches\t\n\tc  est fo----";
	char	str2[] = "u\ttout\tce qu on ----";
	char	str3[] = "peut faire avec\t----";
	char	str4[] = "\n\tprint_memory\n\n----";
	char	str5[] = "\n\tlol.lol\n \0";

	ft_print_memory((void *)empty, sizeof(empty));
	ft_print_memory((void *)str, sizeof(str));
	ft_print_memory((void *)str1, sizeof(str1));
	ft_print_memory((void *)str2, sizeof(str2));
	ft_print_memory((void *)str3, sizeof(str3));
	ft_print_memory((void *)str4, sizeof(str4));
	ft_print_memory((void *)str5, sizeof(str5));

	return (0);
}


