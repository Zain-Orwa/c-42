#include <stdio.h>
#include <unistd.h>

void ft_swap(int *a, int *b){
	int   temp;

	temp = *a;
	*a = *b;
	*b = temp;
}

int main(void)
{
	int v1 = 15;
	int v2 = 35;
	int *a = &v1;
	int *b = &v2;

	printf("Before ft_swap:\n");
	printf("Pointer 'a' points to address %p that has the value %d stored\n", a, *a);
	printf("Pointer 'b' points to address %p that has the value %d stored\n", b, *b);

	ft_swap(a, b);

	printf("\nAfter ft_swap:\n");
	printf("Pointer 'a' remains pointing to address %p, but now that has the value %d stored\n", a, *a);
	printf("Pointer 'b' remains pointing to address %p, but now that has the value %d stored\n", b, *b);

	return (0);
}

