#include <stdlib.h>
#include <stdio.h>

int ft_strlen(char *str){
	int len;

	len = 0;
	while (str[len])
		len++;

	return (len);
}

int calculate_total_length(int size, char **strs, char *sep){
	int i;
	int total_len;

	if (size <= 0)
		return (0);
	
	i = 0;
	total_len = 0;
	while (i < size)
	{
		total_len += ft_strlen(strs[i]);	
		i++;
	}
	total_len += (size - 1) * ft_strlen(sep);

	return (total_len);	
}

char	*ft_strjoin(int size, char **strs, char *sep){
	int  i;
	int  j;
	int  pos;
	int  total_len;
	char *joined_str;

	/* hendle size = 0 case */
	if (size == 0)
	{
		joined_str = (char *)malloc(sizeof(char));
		if (!joined_str)
			return (NULL);
		joined_str[0] = '\0';
		return (joined_str);
	}

	/* allocate memory total memory need it */
	total_len = calculate_total_length(size, strs, sep);
	joined_str = (char *)malloc(sizeof(char) * total_len);
	if (!joined_str)
		return (NULL);

	/* concatenate strings with seperator */
	i   = 0;
	pos = 0;
	while (i < size){

		/* copy current string */
		j = 0;
		while (strs[i][j] != '\0')
			joined_str[pos++] = strs[i][j++];

		/* copy seperator to the string */
			j = 0;
			while (sep[j] && i != size - 1)
				joined_str[pos++] = sep[j++]; 

		i++;
	}
	joined_str[pos] = '\0';

	return (joined_str);
}

int main(void){
	char *joined_str;
	char *strs[] = {
		"Hello", "42", "Network"
	};

	joined_str = ft_strjoin(3, strs, " | ");
	if (!joined_str)
		return (1);

	printf("%s\n", joined_str);
	free(joined_str);

	return (0);
}	
