#include <stdio.h>
#include <unistd.h>

void ft_putstr(char *str){
	char *ptr;

	ptr = str;
	while (*ptr != '\0'){
		write(1, ptr, 1);
		ptr++;
	}
}

int main(){
	char str[] = "Hello Universe";

	ft_putstr(str);

	return (0);
}



