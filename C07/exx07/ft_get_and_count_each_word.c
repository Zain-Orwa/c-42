#include <stdlib.h>
#include <unistd.h>

/* ============================== */
/*            UTILS               */
/* ============================== */

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return ;
	i = 0;
	while (str[i])
	{
		ft_putchar(str[i]);
		i++;
	}
}

void	ft_putnbr(int n)
{
	long	nb;

	nb = n;
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

char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* ============================== */
/*      DYNAMIC STRING READ       */
/* ============================== */

char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;

	if (*size == 0)
		new_size = 32;
	else
		new_size = *size * 2;
	new_str = (char *)malloc(new_size);
	if (!new_str)
		return (NULL);
	if (str)
	{
		ft_strncpy(new_str, str, (int)(*size));
		free(str);
	}
	*size = new_size;
	return (new_str);
}

char	*read_string(void)
{
	char	  ch;
	size_t	length;
	char	  *buffer;
	size_t	buffer_size;

	buffer = NULL;
	buffer_size = 0;
	length = 0;
	ft_putstr("Please Enter Your String:\n");
	while (1)
	{
		if (read(0, &ch, 1) <= 0 || ch == '\n')
			break ;
		if (length + 1 >= buffer_size)
		{
			buffer = ft_realloc_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[length] = ch;
		length++;
	}
	if (buffer)
		buffer[length] = '\0';
	return (buffer);
}

/* ============================== */
/*       WORD COUNT FUNCTION      */
/* ============================== */

int	count_words_in_string(char *str)
{
	int		count;
	char	*start;
	char	*current;

	if (!str)
		return (0);
	count = 0;
	start = str;
	current = str;
	while (*current)
	{
		if (*current == ' ' || *current == '\t' || *current == '\n')
		{
			if (current > start)
				count++;
			start = current + 1;
		}
		current++;
	}
	/* Count last word if string doesn't end with space/tab/newline */
	if (current > start)
		count++;
	return (count);
}

/* ============================== */
/*              MAIN              */
/* ============================== */

int	main(void)
{
	char	*line;
	int		words;

	line = read_string();
	if (!line)
	{
		ft_putstr("Error: could not read string or empty input.\n");
		return (1);
	}
	words = count_words_in_string(line);
	ft_putstr("You entered: \"");
	ft_putstr(line);
	ft_putstr("\"\n");
	ft_putstr("Number of words: ");
	ft_putnbr(words);
	ft_putchar('\n');
	free(line);
	return (0);
}

