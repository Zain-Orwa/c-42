#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i] != '\0')
		i++;

	return (i);
}

/*char *ft_strncat(char *dest, char *src, unsigned int nb){
	unsigned int   i;
	unsigned int   j;

	i = ft_strlen(dest);
	j = 0;
	while (j < nb && src[j] != '\0'){
		dest[i++] = src[j++];
	}
	dest[i] = '\0';
	return (dest);
}*/

char *ft_strncat(char *dest, char *src, unsigned int nb){
	char *ptr;

	ptr = dest;
	while (*ptr)
		ptr++;
	while (*src && nb--)
		*ptr++ = *src++;
	*ptr++ = '\0';
	return (dest);
}

int main(){
	char dest[50] = "Hello,";
	char src[] = " universe";

	printf("%s\n", ft_strncat(dest, src, 4));

	return (0);
}
