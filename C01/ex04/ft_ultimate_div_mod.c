#include <unistd.h>
#include <stdio.h>

void ft_ultimate_div_mod(int *a, int *b){
	int   div;
	int   mod;

	div = (*a / *b);
	mod = (*a % *b);

	*a = div;
	*b = mod;
}


int main(){
	int x;
	int y;

	x = 42;
	y = 8;

	printf("before the division the  value of x is %d, and the value of y is %d\n", x, y);

	ft_ultimate_div_mod(&x, &y);

	printf("after the division the  value of x is %d, and the value of y is %d\n", x, y);


	return (0);
}

