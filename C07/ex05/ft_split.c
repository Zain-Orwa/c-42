#include <stdlib.h>
#include <unistd.h>

int is_sep(char c, char *charset){
	int i;

	i = 0;
	while (charset[i]){
		if (c == charset[i])
			return (1);
		i++;
	}
	return (0);
}

int count_words_in_str(char *str, char *charset){
	int i;
	int count;

	if (!str || !charset)
		return (0);
	
	i = 0;
	count = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset))
		 i++;

		if (str[i] && !is_sep(str[i], charset))
		{
			count++;

			while (str[i] && !is_sep(str[i], charset))
				i++;
		}
	}
	
	return (count);
}

char *ft_strncpy(char *dst, char *src, int size){
	int i ;

	if (!dst || !src || size < 0)
		return (NULL);

	i = 0;
	while (i < size){
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (dst);
}

char **ft_split(char *str, char *charset){
	int  i;
	int  j;
	int  len;
	int  start;
	int  words;
	char **result;

	if (!str || !charset)
		return (NULL);

	words = count_words_in_str(str, charset);
	if (words == 0)
	{
		result = (char**)malloc(sizeof(char*) * 1);
		if (!result)
			return (NULL);
		result[0] = NULL;
		return (result);
	}

	result = (char**)malloc(sizeof(char*) * (words + 1));
	if (!result)
		return (NULL);
	
	i = 0;
	j = 0;
	while (str[i])
	{
		while (str[i] && is_sep(str[i], charset))
			i++;

		if (str[i] && !is_sep(str[i], charset))
		{
			start = i;
			len = 0;

				while (str[i] && !is_sep(str[i], charset))
				{
					len++;
					i++;
				}

				result[j] = malloc(len + 1);
				ft_strncpy(result[j], &str[start], len);
				j++;
		}

	}
	result[j] = NULL;
	return (result);
}

