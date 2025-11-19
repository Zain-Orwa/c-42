#include <stdio.h>
#include <unistd.h>

int ft_strlen(char *str){
	int i;

	i = 0;
	while (str[i])
		i++;

	return (i);
}

char *ft_strcat(char *dest, char *src){
	int i;
	int j;

	i = ft_strlen(dest); 
	j = 0;
	while (src[j] != '\0')
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	dest[i] = '\0';	
	return (dest);
}

/*char    *ft_strcat(char *dest, const char *src)
{
    char *ptr = dest;

    while (*ptr)               // go to end of dest
        ptr++;
    while (*src)               // copy src
    {
        *ptr = *src;
        ptr++;
        src++;
    }
    *ptr = '\0';               // final '\0'
    return (dest);
}*/


int main(){

	char dest[20] = "Hello";
  char src[] = " World";

  ft_strcat(dest, src);
  printf("%s\n", dest);  // -> Hello World

  return 0;

}
