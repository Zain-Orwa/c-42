#include <stdio.h>
#include <unistd.h>

int ft_str_is_alpha(char *str){
	int i;

	i = 0;
	while (str[i] != '\0'){
		if (!((str[i] >= 'A' && str[i] <= 'Z') || (str[i] >= 'a' && str[i] <= 'z'))) 
			return (0);
		
		i++;
	}

	return (1);
}


int main(){
	char	*str1 = " String";
	char	*str2 = "String";
	char  *str3 = "1tring";
	printf("%s is alpha? %d\n", str1, ft_str_is_alpha(str1));
	printf("%s is alpha? %d\n", str2, ft_str_is_alpha(str2));
	printf("%s is alpha? %d\n", str3, ft_str_is_alpha(str3));

	return (0);
}
