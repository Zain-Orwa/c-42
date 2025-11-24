#include <stdio.h>

int ft_strlen(char *str){
	int  i;

	i = 0;
	while (str[i] != '\0')
		i++;

	return (i);
}

int main(){
	char *str = "Letters";

	printf("The string %s, has a length of %d\n", str, ft_strlen(str));

	return (0);
}


