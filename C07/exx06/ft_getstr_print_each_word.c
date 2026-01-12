/*
** string_processor.c
** Simple program to read a string and print each word on a new line
** No static functions - all functions can be used in a library
*/

#include <unistd.h>
#include <stdlib.h>

/* Helper function to print a character */
void	ft_putchar(char c)
{
	write(1, &c, 1);
}

/* Helper function to print a string */
void	ft_putstr(char const *s)
{
	int	i;

	if (!s)
		return ;
	i = 0;
	while (s[i])
		ft_putchar(s[i++]);
}

/* Copy string with size limit */
char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	while (i < size)
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

/* Resize string buffer when needed */
char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;

	if (*size == 0)
		new_size = 32;
	else
		new_size = *size * 2;
	
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (!new_str)
		return (NULL);
	
	if (str)
	{
		ft_strncpy(new_str, str, *size);
		free(str);
	}
	
	*size = new_size;
	return (new_str);
}

/* Read a line from stdin */
char	*read_string(void)
{
	char	*buffer;
	size_t	buffer_size;
	size_t	length;
	char	ch;

	buffer = NULL;
	buffer_size = 0;
	length = 0;
	
	ft_putstr("Please Enter Your String:\n");
	
	while (1)
	{
		/* Read one character and check for EOF/error/newline */
		if (read(0, &ch, 1) <= 0 || ch == '\n')
			break;
		
		/* Resize buffer if needed */
		if (length + 1 >= buffer_size)
		{
			buffer = ft_realloc_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		
		/* Store character */
		buffer[length++] = ch;
	}
	
	/* Null-terminate if we have a buffer */
	if (buffer)
		buffer[length] = '\0';
	
	return (buffer);
}

/* Print each word from string on separate line */
void	print_each_word_in_string(char const *str)
{
	char const	*start;
	char const	*current;

	if (!str)
		return;
	
	start = str;
	current = str;
	
	while (*current)
	{
		if (*current == ' ')
		{
			if (current > start)
			{
				write(1, start, current - start);
				ft_putchar('\n');
			}
			start = current + 1;
		}
		current++;
	}
	
	if (current > start)
	{
		write(1, start, current - start);
		ft_putchar('\n');
	}
}

/* Main program */
int	main(void)
{
	char	*input;

	input = read_string();
	if (!input)
		return (1);
	
	print_each_word_in_string(input);
	
	free(input);
	return (0);
}
