#include <stdio.h>
#include <unistd.h>

int ft_str_is_lowercase(char *str){
	int  i;

	i = 0;
	while (str[i] != '\0'){
		if (!(str[i] >= 'a' && str[i] <= 'z'))
			return (0);
		i++;
	}
	return (1);
}

int main(){
	char *str1 = "abcdefg";
	char *str2 = " abcdefg";
	char *str3 = "abcdefg1";
	char *str4 = "";

	printf("%s is_lower? %d\n", str1, ft_str_is_lowercase(str1));
	printf("%s is_lower? %d\n", str2, ft_str_is_lowercase(str2));
	printf("%s is_lower? %d\n", str3, ft_str_is_lowercase(str3));
	printf("%s is_lower? %d\n", str4, ft_str_is_lowercase(str4));

	return (0);
}
