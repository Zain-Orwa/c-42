#include <stdio.h>
#include <unistd.h>

int ft_str_is_printable(char *str){
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
	char *str3 = "Hello\n";
	char *str4 = "";
	char *str5 = "\tHi";

	printf("%-12s => printable? %d\n", "\"    \"",     ft_str_is_printable(str1));
	printf("%-12s => printable? %d\n", "\"A!1$\"",    ft_str_is_printable(str2));
	printf("%-12s => printable? %d\n", "\"Hello\\n\"", ft_str_is_printable(str3));
	printf("%-12s => printable? %d\n", "\"\"",         ft_str_is_printable(str4));
	printf("%-12s => printable? %d\n", "\"\\tHi\"",    ft_str_is_printable(str5));

	return (0);
}


