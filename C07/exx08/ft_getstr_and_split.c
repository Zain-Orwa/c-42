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

/* ============================== */
/*        DYNAMIC REALLOC         */
/* ============================== */

char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;
	size_t	old_size;

	old_size = *size;
	if (*size == 0)
		new_size = 32;
	else
		new_size = *size * 2;
	new_str = (char *)malloc(sizeof(char) * new_size);
	if (!new_str)
		return (NULL);
	if (str)
	{
		/* copy old buffer contents (up to old_size) */
		ft_strncpy(new_str, str, old_size);
		free(str);
	}
	*size = new_size;
	return (new_str);
}

/* ============================== */
/*          READ STRING           */
/* ============================== */

char	*read_string(void)
{
	char	ch;
	size_t	length;
	char	*buffer;
	size_t	buffer_size;

	length = 0;
	buffer = NULL;
	buffer_size = 0;
	ft_putstr("Please Enter Your String:\n");

	while (1)
	{
		if (read(0, &ch, 1) <= 0 || ch == '\n')
			break;
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
/*        TOKEN FUNCTIONS         */
/* ============================== */

int	is_Delimiter(char c, char *delim)
{
	int	i;

	i = 0;
	while (delim[i])
	{
		if (c == delim[i])
			return (1);
		i++;
	}
	return (0);
}

int	count_tokens_in_str(char *str, char *delim)
{
	int		count;
	char	*start;
	char	*current;

	if (!str || !delim)
		return (0);
	count = 0;
	start = str;
	current = str;
	while (*current)
	{
		if (is_Delimiter(*current, delim))
		{
			if (current > start)
				count++;
			start = current + 1;
		}
		current++;
	}
	if (current > start)
		count++;
	return (count);
}

char	**split_string(char *str, char *delim)
{
	int		i;
	int		j;
	int		len;
	int		words;
	int		start;
	char	**result;

	if (!str || !delim)
		return (NULL);
	words = count_tokens_in_str(str, delim);
	result = (char **)malloc(sizeof(char *) * (words + 1));
	if (!result)
		return (NULL);
	i = 0;
	j = 0;
	while (j < words)
	{
		while (str[i] && is_Delimiter(str[i], delim))
			i++;
		if (str[i] && !is_Delimiter(str[i], delim))
		{
			len = 0;
			start = i;
			while (str[i] && !is_Delimiter(str[i], delim))
			{
				len++;
				i++;
			}
			result[j] = (char *)malloc(sizeof(char) * (len + 1));
			if (!result[j])
				return (NULL);
			ft_strncpy(result[j], &str[start], len);
			j++;
		}
	}
	result[j] = NULL;
	return (result);
}

/* ============================== */
/*     PRINT & FREE FUNCTIONS     */
/* ============================== */

void	print_split_result(char **result)
{
	int	i;

	if (!result)
	{
		ft_putstr("Result is NULL\n");
		return;
	}
	i = 0;
	while (result[i])
	{
		ft_putstr(result[i]);
		ft_putstr("\n");
		i++;
	}
}

void	free_split_result(char **result)
{
	int	i;

	if (!result)
		return;
	i = 0;
	while (result[i])
	{
		free(result[i]);
		i++;
	}
	free(result);
}

/* ============================== */
/*              MAIN              */
/* ============================== */

int	main(void)
{
	char	*input;
	char	**tokens;
	int		token_count;
	char	*delim;

	delim = " \t\n";

	input = read_string();
	if (!input)
		return (1);

	token_count = count_tokens_in_str(input, delim);
	ft_putstr("Tokens = ");
	ft_putnbr(token_count);
	ft_putstr("\n");

	tokens = split_string(input, delim);
	if (!tokens)
	{
		free(input);
		return (1);
	}

	print_split_result(tokens);

	free_split_result(tokens);
	free(input);
	return (0);
}

