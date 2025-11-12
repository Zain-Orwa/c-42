#include <stdio.h>
#include <unistd.h>

int ft_str_is_numeric(char *str){
	int  i;

	i = 0;
	while (str[i] != '\0'){
		if (!(str[i] >= '0' && str[i] <= '9'))
			return (0);
		i++;
	}
	return (1);
}


int main(){
	char *str1 = "1234";
	char *str2 = "A1R2";
	char *str3 = "";

	printf("%s is numeric? %d\n", str1, ft_str_is_numeric(str1));
	printf("%s is numeric? %d\n", str2, ft_str_is_numeric(str2));
	printf("%s is numeric? %d\n", str3, ft_str_is_numeric(str3));

	return (0);
}
