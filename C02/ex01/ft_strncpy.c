#include <stdio.h>
#include <unistd.h>

char *ft_strncpy(char *dest, char *src, unsigned int n){

	unsigned	int i;

	i = 0;
	while (i < n && src[i] != '\0'){
		dest[i] = src[i];
		i++;
	}
	
	while (i < n){
		dest[i] = '\0';
		i++;
	}

	return (dest);
}


int main(){

  char	dest[] = "######";
	char	src[] = "Source";
	int	n = 2;
	
	printf("dest before: %s\n", dest);
	ft_strncpy(dest, src, n);
	printf("dest after: %s\n", dest);

	return (0);
}
