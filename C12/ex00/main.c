#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

int	main(void)
{
	t_list	*elem1;
	t_list	*elem2;
	int		a;
	char	*str;

	a = 42;
	str = "Hello World!";

	// Test with integer
	elem1 = ft_create_elem(&a);
	if (elem1)
	{
		printf("Element 1 - Data: %d\n", *(int *)(elem1->data));
		printf("Element 1 - Next: %p\n", (void *)(elem1->next));
	}
	else
		printf("Failed to create element 1\n");

	// Test with string
	elem2 = ft_create_elem(str);
	if (elem2)
	{
		printf("Element 2 - Data: %s\n", (char *)(elem2->data));
		printf("Element 2 - Next: %p\n", (void *)(elem2->next));
	}
	else
		printf("Failed to create element 2\n");

	// Test linking elements (optional, to show they can be linked)
	if (elem1 && elem2)
	{
		elem1->next = elem2;
		printf("After linking:\n");
		printf("Element 1 next points to: %p\n", (void *)(elem1->next));
		printf("Element 1 next data: %s\n", (char *)(elem1->next->data));
	}

	// Test with NULL data
	t_list	*elem3;
	elem3 = ft_create_elem(NULL);
	if (elem3)
	{
		printf("Element 3 - Data: %p\n", elem3->data);
		printf("Element 3 - Next: %p\n", (void *)(elem3->next));
	}
	else
		printf("Failed to create element 3\n");

	// Free allocated memory (though in this simple test it's not strictly necessary)
	free(elem1);
	free(elem2);
	free(elem3);

	return (0);
}

