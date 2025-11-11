#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


char *ft_strcpy(char *dest, char *src){
	int i;

	i = 0;

	while (src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	
	return (dest);
}


int main(){
	char src[] = {"Hello Univers!"};
	char dest[20];

	ft_strcpy(dest, src);
	printf("%s", dest);

	
	return (0);
}
