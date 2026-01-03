#include <stdlib.h>


size_t ft_strlen(const char *str){
	size_t i;

	i = 0;
	while (str[i])
		i++;

	return (i);
}

char *ft_strdup(char *src){
	char   *dst;
	size_t len;
	size_t i;

	if (!src)
		return (NULL);

	len = ft_strlen(src);
	dst	= (char*)malloc(len + 1);  // sizeof(char) is always 1, so we can omit it
	//dst = (char*)malloc(sizeof(char) * (len + 1));
	
	if (!dst)
		return (NULL);

	i = 0;
	while (i < len){
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';

	return (dst);
}

#include <stdio.h>
#include <stdlib.h>

/* declare your function */
char *ft_strdup(char *src);

int main(void)
{
    char *src1 = "Hello 42!";
    char *dup1 = ft_strdup(src1);

    if (!dup1)
    {
        printf("ft_strdup failed (malloc returned NULL)\n");
        return 1;
    }

    printf("src1: %s\n", src1);
    printf("dup1: %s\n", dup1);

    /* prove it's a different memory address */
    printf("src1 address: %p\n", (void *)src1);
    printf("dup1 address: %p\n", (void *)dup1);

    free(dup1);

    /* test empty string */
    char *src2 = "";
    char *dup2 = ft_strdup(src2);
    if (!dup2)
    {
        printf("ft_strdup failed on empty string\n");
        return 1;
    }
    printf("src2: '%s'\n", src2);
    printf("dup2: '%s'\n", dup2);
    free(dup2);

    /* test NULL input (your function returns NULL) */
    char *dup3 = ft_strdup(NULL);
    printf("dup3 (NULL input): %p\n", (void *)dup3);

    return 0;
}

