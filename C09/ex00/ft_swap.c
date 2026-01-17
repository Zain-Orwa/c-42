/* ft_swap.c */

void ft_swap(int *a, int *b){
	int temp;

	temp = *a;
	*a   = *b;
	*b   = temp;
}

