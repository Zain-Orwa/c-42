#include <unistd.h>
#include <stdio.h>

void ft_ft(int *nbr)
{
	*nbr = 42;
}

int main(void)
{
	int n = 5;
	int *nbr = &n;

	printf("Before ft_ft:\n");
	printf("Variable 'n' is stored at address %p and holds the value %d\n", &n, n);
	printf("Pointer 'nbr' points to the same address %p and dereferencing it gives the value %d\n", nbr, *nbr);

	ft_ft(nbr);

	printf("\nAfter ft_ft:\n");
	printf("Pointer 'nbr' still points to address %p, but now that memory holds the value %d\n", nbr, *nbr);
	printf("The variable 'n' now has the new value %d stored.\n", n);

	return (0);
}

