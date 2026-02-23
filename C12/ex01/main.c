#include <stdio.h>
#include "ft_list.h"

int main(void)
{
	t_list *list = NULL;
	int a = 42;
	char *str = "Hello";

	ft_list_push_front(&list, &a);
  ft_list_push_front(&list, str);

printf("First element data: %s\n", (char *)list->data);
printf("Second element data: %d\n", *(int *)list->next->data);

	return (0);
}

