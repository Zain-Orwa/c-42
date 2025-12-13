#include <unistd.h>
#include <stdio.h>

void ft_putstr(char *str){
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

int ft_strcmp(char *s1, char *s2){
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}

	return ((unsigned char)*s1 - (unsigned char)*s2);
}

void ft_swap(char **a, char **b){
	char *temp;

	temp = *a;
	*a   = *b;
	*b   = temp;
}

void ft_sort_params(int argc, char *argv[]){
	int i;
	int j;

	i = 1;
	while (i < argc - 1)
	{
		j = 1;
		while (j < argc - 1)
		{
			if (ft_strcmp(argv[j], argv[j + 1]) > 0)
				ft_swap(&argv[j], &argv[j + 1]);
			j++;
		}
		i++;
	}
}

int main(int argc, char *argv[]){
	int i;

	ft_sort_params(argc, argv);

	i = 1;
	while (i < argc)
	{
		ft_putstr(argv[i]);	
		i++;
	}


	return (0);
}

