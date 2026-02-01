#include <unistd.h>

int ft_strlen(char *str){
	char *start;

	start = str;
	while (*str)
		str++;

	return (str - start);
}

void ft_putstr(char *str){
	write(1, str, ft_strlen(str));
}



int main(){
	char *str = {"print a string!\n"};

	ft_putstr(str);

	return (0);
}
