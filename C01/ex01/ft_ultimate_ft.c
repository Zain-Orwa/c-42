#include <stdio.h>

void ft_ultimate_ft(int *********nbr){
	*********nbr = 42;
}

int main(void)
{
	int number = 1024;
	int *ptr1 = &number;
	int **ptr2 = &ptr1;
	int ***ptr3 = &ptr2;
	int ****ptr4 = &ptr3;
	int *****ptr5 = &ptr4;
	int ******ptr6 = &ptr5;
	int *******ptr7 = &ptr6;
	int ********ptr8 = &ptr7;
	int *********ptr9 = &ptr8;

	printf("'number' is at address %p and has value %d\n", &number, number);
	printf("'ptr1' points to address %p and dereferencing it gives value %d\n", ptr1, *ptr1);
	printf("'ptr9' points to address %p but connects all the way down to 'number' value %d\n", ptr9, *********ptr9);

	ft_ultimate_ft(ptr9);

	printf("\nAfter ft_ultimate_ft:\n");
	printf("'ptr9' still points to address %p, but that address now holds value %d\n", ptr9, *********ptr9);
	printf("'number' now has the value %d stored at the same address %p\n", number, &number);

	return (0);
}

