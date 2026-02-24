#include <stdio.h>
#include <stdlib.h>
#include "ft_list.h"

// Helper function to print list size with description
void	print_list_size(t_list *list, char *description)
{
	printf("%s: %d element(s)\n", description, ft_list_size(list));
}

// Helper function to free the entire list
void	free_list(t_list *list)
{
	t_list	*tmp;

	while (list)
	{
		tmp = list->next;
		free(list);
		list = tmp;
	}
}

int	main(void)
{
	t_list	*list;
	int		a;
	int		b;
	int		c;
	char	*str1;
	char	*str2;

	// Initialize data
	a = 42;
	b = 21;
	c = 84;
	str1 = "Hello";
	str2 = "World";

	printf("\n=== TESTING ft_list_size ===\n\n");

	// Test 1: Empty list
	printf("Test 1: Empty list\n");
	list = NULL;
	print_list_size(list, "Size of empty list");
	printf("Expected: 0\n\n");

	// Test 2: List with 1 element
	printf("Test 2: List with 1 element\n");
	list = ft_create_elem(&a);
	print_list_size(list, "Size after 1 element");
	printf("Expected: 1\n\n");

	// Test 3: List with 2 elements
	printf("Test 3: List with 2 elements\n");
	ft_list_push_front(&list, str1);
	print_list_size(list, "Size after 2 elements");
	printf("Expected: 2\n");
	printf("First element data: %s\n", (char *)list->data);
	printf("Second element data: %d\n", *(int *)list->next->data);
	printf("\n");

	// Test 4: List with 3 elements
	printf("Test 4: List with 3 elements\n");
	ft_list_push_front(&list, &b);
	print_list_size(list, "Size after 3 elements");
	printf("Expected: 3\n");
	printf("First element data: %d\n", *(int *)list->data);
	printf("Second element data: %s\n", (char *)list->next->data);
	printf("Third element data: %d\n", *(int *)list->next->next->data);
	printf("\n");

	// Test 5: List with 4 elements
	printf("Test 5: List with 4 elements\n");
	ft_list_push_front(&list, str2);
	print_list_size(list, "Size after 4 elements");
	printf("Expected: 4\n");
	printf("First element data: %s\n", (char *)list->data);
	printf("Second element data: %d\n", *(int *)list->next->data);
	printf("Third element data: %s\n", (char *)list->next->next->data);
	printf("Fourth element data: %d\n", *(int *)list->next->next->next->data);
	printf("\n");

	// Test 6: List with 5 elements
	printf("Test 6: List with 5 elements\n");
	ft_list_push_front(&list, &c);
	print_list_size(list, "Size after 5 elements");
	printf("Expected: 5\n\n");

	// Test 7: Verify list integrity
	printf("Test 7: Traverse and print all elements\n");
	printf("List contents (from first to last):\n");
	t_list *current = list;
	int index = 1;
	while (current)
	{
		if (index == 1)
			printf("  Element %d: %s\n", index, (char *)current->data);
		else if (index == 2)
			printf("  Element %d: %d\n", index, *(int *)current->data);
		else if (index == 3)
			printf("  Element %d: %s\n", index, (char *)current->data);
		else if (index == 4)
			printf("  Element %d: %d\n", index, *(int *)current->data);
		else if (index == 5)
			printf("  Element %d: %d\n", index, *(int *)current->data);
		current = current->next;
		index++;
	}
	printf("\n");

	// Test 8: Size after removing one element (simulate by moving pointer)
	printf("Test 8: Size from second element onwards\n");
	print_list_size(list->next, "Size starting from second element");
	printf("Expected: 4\n\n");

	// Test 9: Verify size function doesn't modify the list
	printf("Test 9: Verify list unchanged after size calls\n");
	printf("Calling ft_list_size multiple times:\n");
	for (int i = 0; i < 3; i++)
	{
		printf("  Call %d: size = %d\n", i + 1, ft_list_size(list));
	}
	printf("List still has 5 elements\n\n");

	// Test 10: Edge case - NULL pointer
	printf("Test 10: Edge case - passing NULL\n");
	print_list_size(NULL, "Size of NULL");
	printf("Expected: 0\n\n");

	// Clean up
	printf("Cleaning up...\n");
	free_list(list);
	printf("Done!\n");

	return (0);
}

