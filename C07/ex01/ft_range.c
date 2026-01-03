#include <stdio.h>
#include <stdlib.h>


int *ft_range(int min, int max){
	int *range;
	int size;
	int i;

	if (min >= max)
		return (NULL);

	size = max - min;
	range = (int*)malloc(sizeof(int) * size);
	if (!range)
		return (NULL);

	i = 0;
	while (i < size){
		range[i] = min + i;
		i++;
	}

	return (range);	
}

int main(void)
{
    int *arr;
    int i;
    int min = 3;
    int max = 7;

    arr = ft_range(min, max);
    if (!arr)
    {
        printf("ft_range returned NULL\n");
        return 1;
    }

    i = 0;
    while (i < max - min)
    {
        printf("%d ", arr[i]);
        i++;
    }
    printf("\n");

    free(arr);
    return 0;
}
