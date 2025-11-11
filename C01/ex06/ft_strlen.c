#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i])
		i++;

	return (i);
}

int main(){
	char *str = {"strlen is counting"};
	ft_strlen(str);

	printf("Number of char in string: %d\n", ft_strlen(str));

	return (0);
}
