#include <stdio.h>

char    *ft_strstr(char *str, char *to_find)
{
    char *s;        // pointer for walking through str
    char *find;     // pointer for walking through to_find

    if (*to_find == '\0')       // empty needle → return whole haystack
        return (str);

    while (*str)                // while not at end of str
    {
        s = str;                // candidate starting position
        find = to_find;

        while (*find && *s == *find)    // while chars match and not end of needle
        {
            s++;
            find++;
        }

        if (*find == '\0')      // did we reach the end of to_find?
            return (str);       // yes → match found! return start position

        str++;                  // no match → try next position in str
    }
    return (0);                 // not found
}

int main(void)
{
    char str[] = "Hello World";
    char find1[] = "World";
    char find2[] = "lo Wo";
    char find3[] = "xyz";
    char find4[] = "";

    printf("%s\n", ft_strstr(str, find1));  // → World
    printf("%s\n", ft_strstr(str, find2));  // → (null)
    printf("%s\n", ft_strstr(str, find3));  // → (null)
    printf("%s\n", ft_strstr(str, find4));  // → Hello World

    return (0);
}


/*
#include <stdio.h>

char *ft_strstr(char *str, char *to_find){
	int i;
	int j;

	if (to_find[0] == '\0')
		return (str);

	i = 0;
	while (str[i] != '\0')
	{
		j = 0;
		while (to_find[j] != '\0' && str[i + j] == to_find[j])
			j++;

		if (to_find[j] == '\0')
			return (&str[i]);

		i++;
	}
	return (0);
}


int main(){
	char str[] = "Hello World";
	char find1[] = "World";
	char find2[] = "lo Wo";
	char find3[] = "xyz";
	char find4[] = "";

	printf("%s\n", ft_strstr(str, find1));
	printf("%s\n", ft_strstr(str, find2));
	printf("%s\n", ft_strstr(str, find3));
	printf("%s\n", ft_strstr(str, find4));

	return (0);
}
*/
