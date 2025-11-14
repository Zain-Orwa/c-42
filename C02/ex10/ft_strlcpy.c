#include <stdio.h>

int ft_strlen(char *str){
	int   i;

	i = 0;
	while (str[i]){
		i++;
	}

	return (i);
}

unsigned int ft_strlcpy(char *dest, char *src, unsigned int size){
	unsigned int i;

	i = 0;
	if (size > 0)
	{

		while(src[i] != '\0' && i < size - 1)
		{
			dest[i] = src[i];
			i++;
		}

		dest[i] = '\0';
	}
	
	return (ft_strlen(src));
}

int main(){
	char src[] = "letters";
	char dest[11];
	int n = 6;

	printf("src: %s\nlength returned: %d\ndest: %s\n", src, ft_strlcpy(dest, src, n), dest);

	return (0);
}

