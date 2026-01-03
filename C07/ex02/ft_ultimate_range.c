#include <stdlib.h>
#include <stdio.h>

int ft_ultimate_range(int **range, int min, int max){
	int size;
	int i;

	if (min >= max){
		*range = NULL;
		return (0);
	}

	size = max - min;
	*range = (int*)malloc(sizeof(int) * size);
	if (!*range)
		return (-1);

	i = 0;
	while (i < size){
		(*range)[i] = min + i;
		i++;
	}

	return (size);
}


/*
 int ft_ultimate_range(int **range, int min, int max)
{
    int *arr;
    int i;
    int size;
    
    if (min >= max)
    {
        *range = NULL;
        return (0);
    }
    
    size = max - min;
    arr = malloc(sizeof(int) * size);  // size is positive int
    
    if (arr == NULL)
        return (-1);
    
    *range = arr;  // Assign the allocated array
    
    i = 0;
    while (i < size)
    {
        arr[i] = min + i;  // Use arr directly, no (*range)[i] needed
        i++;
    }
    
    return (size);
}
  */

int main(void)
{
    int *arr;
    int size;
    int i;

    printf("=== Testing ft_ultimate_range ===\n\n");

    // Test 1: Normal range
    printf("Test 1: ft_ultimate_range(&arr, 3, 7)\n");
    size = ft_ultimate_range(&arr, 3, 7);
    printf("Returned: %d\n", size);
    printf("Expected: 4\n");
    if (size > 0)
    {
        printf("Array: ");
        for (i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\nExpected: 3 4 5 6\n");
        free(arr);
    }
    printf("---\n\n");

    // Test 2: Negative to positive
    printf("Test 2: ft_ultimate_range(&arr, -2, 3)\n");
    size = ft_ultimate_range(&arr, -2, 3);
    printf("Returned: %d\n", size);
    printf("Expected: 5\n");
    if (size > 0)
    {
        printf("Array: ");
        for (i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\nExpected: -2 -1 0 1 2\n");
        free(arr);
    }
    printf("---\n\n");

    // Test 3: min >= max (equal)
    printf("Test 3: ft_ultimate_range(&arr, 5, 5)\n");
    size = ft_ultimate_range(&arr, 5, 5);
    printf("Returned: %d\n", size);
    printf("Expected: 0 (and arr should be NULL)\n");
    printf("arr == NULL? %s\n", arr == NULL ? "YES" : "NO");
    printf("---\n\n");

    // Test 4: min > max
    printf("Test 4: ft_ultimate_range(&arr, 10, 5)\n");
    size = ft_ultimate_range(&arr, 10, 5);
    printf("Returned: %d\n", size);
    printf("Expected: 0 (and arr should be NULL)\n");
    printf("arr == NULL? %s\n", arr == NULL ? "YES" : "NO");
    printf("---\n\n");

    // Test 5: Single element range
    printf("Test 5: ft_ultimate_range(&arr, 42, 43)\n");
    size = ft_ultimate_range(&arr, 42, 43);
    printf("Returned: %d\n", size);
    printf("Expected: 1\n");
    if (size > 0)
    {
        printf("Array: ");
        for (i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\nExpected: 42\n");
        free(arr);
    }
    printf("---\n\n");

    // Test 6: Large range
    printf("Test 6: ft_ultimate_range(&arr, 0, 10)\n");
    size = ft_ultimate_range(&arr, 0, 10);
    printf("Returned: %d\n", size);
    printf("Expected: 10\n");
    if (size > 0)
    {
        printf("First 5 elements: ");
        for (i = 0; i < 5 && i < size; i++)
            printf("%d ", arr[i]);
        printf("\nLast 5 elements: ");
        for (i = size - 5; i < size; i++)
            printf("%d ", arr[i]);
        printf("\n");
        free(arr);
    }
    printf("---\n\n");

    // Test 7: Very negative range
    printf("Test 7: ft_ultimate_range(&arr, -5, -1)\n");
    size = ft_ultimate_range(&arr, -5, -1);
    printf("Returned: %d\n", size);
    printf("Expected: 4\n");
    if (size > 0)
    {
        printf("Array: ");
        for (i = 0; i < size; i++)
            printf("%d ", arr[i]);
        printf("\nExpected: -5 -4 -3 -2\n");
        free(arr);
    }
    printf("---\n\n");

    return (0);
}

