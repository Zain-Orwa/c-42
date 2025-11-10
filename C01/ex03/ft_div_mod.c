#include <unistd.h>
#include <stdio.h>


void ft_div_mod(int a, int b, int *div, int *mod){
	*div = (a / b);
	*mod = (a % b);
}

int main(void)
{
	int a = 45;
	int b = 5;
	int *div = &a;
	int *mod = &b;

	printf("Before ft_div_mod:\n");
	printf("Pointer 'div' points to address %p that has the value %d stored\n", div, *div);
	printf("Pointer 'mod' points to address %p that has the value %d stored\n", mod, *mod);

	ft_div_mod(a, b, div, mod);

	printf("\nAfter ft_div_mod:\n");
	printf("Pointer 'div' remains pointing to address %p, but now that has the value %d stored\n", div, *div);
	printf("Pointer 'mod' remains pointing to address %p, but now that has the value %d stored\n", mod, *mod);

	return (0);
}
