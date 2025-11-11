#include <stdio.h>
#include <unistd.h>

void ft_rev_int_tab(int *tab, int size){
	int i;
	int j;

	i = 0;
	j = size - 1;
	while (i < j){
		int temp = tab[i];
		tab[i] = tab[j];
		tab[j] = temp;
		i++;
		j--;
	}
}


int main(){
	int tab[] = {1, 2, 3, 4, 5};
	int size = (int)(sizeof(tab) / sizeof(tab[0]));

	ft_rev_int_tab(tab, size);

	for (int i = 0; i < size; i++){
		printf("%d ", tab[i]);
  }

	return (0);
}
