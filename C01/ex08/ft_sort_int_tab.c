#include <stdio.h>
#include <unistd.h>

void ft_sort_int_tab(int *tab, int size){
	int i;
	int temp;
	int swapped;

	swapped = 1;
	while (swapped){
		swapped = 0;
		i = 0;
		while (i < size - 1){
			if (tab[i] > tab[i + 1]){
				temp = tab[i];
				tab[i] = tab[i+1];
				tab[i+1] = temp;
				swapped = 1;
			}
			i++;
		}
		size--;
	}
}

int main(){
	int tab[] = {4, -1, 5, 3, 9, 8, 7};
	int size = (int)(sizeof(tab) / sizeof(tab[0]));

	ft_sort_int_tab(tab, size);
	for (int i = 0; i < size; i++){
		printf("%d ", tab[i]);
	}

	return (0);
}
