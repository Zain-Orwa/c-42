#include <stdio.h>

unsigned int ft_strlcat(char *dest, char *src, unsigned int size){
	unsigned int dest_len;
	unsigned int src_len;
	unsigned int i;

	dest_len = 0;
	while (dest_len < size && dest[dest_len] != '\0')
		dest_len++;

	src_len = 0;
	while (src[src_len] != '\0')
		src_len++;

	if (dest_len == size)
		return (size + src_len);

	i = 0;
	while (src[i] != '\0' && (dest_len + i + 1) < size){
		dest[dest_len + i] = src[i];
		i++;
	}
	dest[dest_len + i] = '\0';

	return (dest_len + src_len);
}

int main(void)
{
    char buffer1[20] = "Hello";
    char buffer2[10] = "Hello";
    char buffer3[5] = "Hi";

    char src[] = " World!";
    unsigned int ret;

    printf("=== Test 1: Normal concat (size > dest_len) ===\n");
    printf("Before: \"%s\"\n", buffer1);
    ret = ft_strlcat(buffer1, src, 20);
    printf("After : \"%s\"\n", buffer1);
    printf("Return: %u\n\n", ret);

    printf("=== Test 2: Small size (truncation expected) ===\n");
    printf("Before: \"%s\"\n", buffer2);
    ret = ft_strlcat(buffer2, src, 10);
    printf("After : \"%s\"\n", buffer2);
    printf("Return: %u\n\n", ret);

    printf("=== Test 3: size <= dest_len (no concat) ===\n");
    printf("Before: \"%s\"\n", buffer3);
    ret = ft_strlcat(buffer3, src, 2);  // size smaller than existing "Hi"
    printf("After : \"%s\"\n", buffer3);
    printf("Return: %u\n\n", ret);

    printf("=== Test 4: size = 0 ===\n");
    char buffer4[20] = "Test";
    ret = ft_strlcat(buffer4, src, 0);
    printf("Buffer unchanged: \"%s\"\n", buffer4);
    printf("Return: %u\n\n", ret);

    return 0;
}
