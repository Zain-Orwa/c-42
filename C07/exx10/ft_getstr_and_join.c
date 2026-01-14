/* get two strings and join them*/
#include <stdlib.h>
#include <unistd.h>

/* ============================== */
/*             UTILS              */
/* ============================== */

void	ft_putchar(char c)
{
	write(1, &c, 1);
}

void	ft_putstr(char *str)
{
	int	i;

	if (!str)
		return;
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

	if (!src || !dst)
		return (NULL);
	i = 0;
	while (i < size && src[i])
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

int	ft_strlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (str[len])
		len++;
	return (len);
}

/* ============================== */
/*         REALLOC STRING         */
/* ============================== */

char	*ft_realloc_str(char *str, size_t *size)
{
	char	*new_str;
	size_t	old_size;
	size_t	new_size;

	if (!size)
		return (NULL);
	old_size = *size;
	if (old_size == 0)
		new_size = 32;
	else
		new_size = old_size * 2;
	new_str = (char *)malloc(sizeof(char) * (new_size + 1));
	if (!new_str)
		return (NULL);
	if (str)
	{
		/* copy at most old_size chars, stop early at '\0' */
		ft_strncpy(new_str, str, (int)old_size);
		free(str);
	}
	else
		new_str[0] = '\0';
	*size = new_size;
	return (new_str);
}

/* ============================== */
/*         READ ONE LINE          */
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
	while (read(0, &ch, 1) > 0 && ch != '\n')
	{
		if (length + 2 >= buffer_size)
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
/*          JOIN STRINGS          */
/* ============================== */

char	*ft_join_str(char *str1, char *str2)
{
	int		 s1_len;
	int		 s2_len;
	size_t total_len;
	char	 *joined_str;

	if (!str1 || !str2)
		return (NULL);

	s1_len = ft_strlen(str1);
	s2_len = ft_strlen(str2);

	/* str1 + space + str2 + '\0' */
	total_len = (size_t)s1_len + 1 + (size_t)s2_len;
	joined_str = (char *)malloc(sizeof(char) * (total_len + 1));
	if (!joined_str)
		return (NULL);

	/* copy str1 */
	ft_strncpy(joined_str, str1, s1_len);

	/* add space after str1 */
	joined_str[s1_len] = ' ';

	/* copy str2 after the space */
	ft_strncpy(joined_str + s1_len + 1, str2, s2_len);

	return (joined_str);
}

/* ============================== */
/*              MAIN              */
/* ============================== */

int	main(void)
{
	char	*str1;
	char	*str2;
	char	*joined;

	ft_putstr("Enter first string:\n");
	str1 = read_string();
	if (!str1)
		return (1);

	ft_putstr("Enter second string:\n");
	str2 = read_string();
	if (!str2)
	{
		free(str1);
		return (1);
	}

	joined = ft_join_str(str1, str2);
	if (!joined)
	{
		free(str1);
		free(str2);
		return (1);
	}

	ft_putstr("Joined: ");
	ft_putstr(joined);
	ft_putchar('\n');

	free(str1);
	free(str2);
	free(joined);
	return (0);
}

