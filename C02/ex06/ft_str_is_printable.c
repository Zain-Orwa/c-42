#include <stdio.h>
#include <unistd.h>

int ft_str_is_uppercase(char *str){
	int  i;

	i = 0;
	while (str[i] != '\0'){
		if (!(str[i] >= 32 && str[i] <= 126))
			return (0);
		i++;
	}
	return (1);
}

int main(){
	char *str1 = "    ";
	char *str2 = "A!1$";

	printf("%s is_upper? %d\n", str1, ft_str_is_uppercase(str1));
	printf("%s is_upper? %d\n", str2, ft_str_is_uppercase(str2));

	return (0);
}


