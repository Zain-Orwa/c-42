#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}


void ft_ft(int *nbr){
	*nbr = 42;
}

int main(){
	int   n = 5;
	int   *nbr = &n;

	printf("Before ft_ft: \n");
	printf("Variable 'nbr' points to adress %p that has the value %d stored\n", &n, n);
	printf("Pointer 'nbr' points to the same adress %p that has the value %d stored\n", nbr, *nbr);
	ft_ft(nbr);
	printf("\n");
	printf("After ft_ft: \n");
	printf("Pointer 'nbr' remains pointing to adress %p, but now that has the value %d stored\n", nbr, *nbr);
	printf("Now 'n' has the value %d stored\n", n);

	return (0);
}
