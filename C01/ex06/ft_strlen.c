#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str){
	char *start;

	start = str;
	while (*str)
		str++;
	return (str - start);
}

int main(){
	char *str = {"strlen is counting"};
	ft_strlen(str);

	printf("Number of characters in the string: %d\n", ft_strlen(str));

	return (0);
}
