/* trim left, right and all */
#include <stdlib.h>
#include <unistd.h>

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

char	*ft_strncpy(char *dst, char *src, int size)
{
	int	i;

	i = 0;
	// Only copy if src is not NULL
	if (!src || !dst)
		return (dst);
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char *ft_reall_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	new_size;
	size_t	old_size;

	old_size = *size;
	new_size = (old_size == 0) ? 32 : old_size * 2;
	
	new_str = (char*)malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	
	if (str)
	{
		// Copy old data into new buffer
		int i = 0;
		while (i < (int)old_size && str[i])
		{
			new_str[i] = str[i];
			i++;
		}
		new_str[i] = '\0';
		free(str);
	}
	else
		new_str[0] = '\0';

	*size = new_size;
	return (new_str);
}

char *read_string(void)
{
	char	  ch;
	size_t	length;
	char	  *buffer;
	size_t	buffer_size;

	length = 0;
	buffer = NULL;
	buffer_size = 0;

	ft_putstr("Please Enter Your String:\n");

	while (read(0, &ch, 1) > 0 && ch != '\n')
	{
		// +1 for the character, +1 for the null terminator
		if (length + 2 >= buffer_size)
		{
			buffer = ft_reall_str(buffer, &buffer_size);
			if (!buffer)
				return (NULL);
		}
		buffer[length++] = ch;
	}

	if (buffer)
		buffer[length] = '\0';
	return (buffer);
}

int ft_strlen(char *str)
{
	int i = 0;
	if (!str) return (0);
	while (str[i])
		i++;
	return (i);
}

char *ft_trim_left(char *str)
{
	int i = 0;
	int j = 0;

	if (!str)
		return (NULL);

	while (str[i] == ' ' || str[i] == '\t')
		i++;

	if (i == 0)
		return (str);

	while (str[i])
		str[j++] = str[i++];

	str[j] = '\0';
	return (str);
}

char *ft_trim_right(char *str)
{
	int len;

	if (!str || (len = ft_strlen(str)) == 0)
		return (str);

	while (len > 0 && (str[len - 1] == ' ' || str[len - 1] == '\t'))
		len--;

	str[len] = '\0';
	return (str);
}

char *ft_trim_all(char *str)
{
	return (ft_trim_left(ft_trim_right(str)));
}

int main(void)
{
	char *input;

	/* --- LEFT TRIM SECTION --- */
	input = read_string();
	if (input)
	{
		ft_putstr("\nOriginal: \"");
		ft_putstr(input);
		ft_putstr("\"\n");

		ft_trim_left(input);
		ft_putstr("Left Trim: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	/* --- RIGHT TRIM SECTION --- */
	input = read_string();
	if (input)
	{
		ft_trim_right(input);
		ft_putstr("Right Trim: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	/* --- TRIM ALL SECTION --- */
	input = read_string();
	if (input)
	{
		ft_trim_all(input);
		ft_putstr("Trim All: \"");
		ft_putstr(input);
		ft_putstr("\"\n");
		free(input);
	}

	return (0);
}
