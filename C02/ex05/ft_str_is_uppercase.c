#include <stdio.h>
#include <unistd.h>

int ft_str_is_uppercase(char *str){
	int  i;

	i = 0;
	while (str[i] != '\0'){
		if (!(str[i] >= 'A' && str[i] <= 'Z'))
			return (0);
		i++;
	}
	return (1);
}

int main(){
	char *str1 = "ABCDEFGG";
	char *str2 = "abcdefg";
	char *str3 = "abcdefg1";
	char *str4 = "";

	printf("%s is_upper? %d\n", str1, ft_str_is_uppercase(str1));
	printf("%s is_upper? %d\n", str2, ft_str_is_uppercase(str2));
	printf("%s is_upper? %d\n", str3, ft_str_is_uppercase(str3));
	printf("%s is_upper? %d\n", str4, ft_str_is_uppercase(str4));

	return (0);
}

