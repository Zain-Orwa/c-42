#include <stdio.h>

int ft_strlen(char *str){
	char *ptr;

	ptr = str;
	while (*ptr != '\0')
		ptr++;

	return (ptr - str);
}

int main(){
	char *str = "Letters";

	printf("The string %s, has a length of %d\n", str, ft_strlen(str));

	return (0);
}


