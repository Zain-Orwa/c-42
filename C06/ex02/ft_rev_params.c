#include <unistd.h>
#include <stdio.h>

/*void ft_putchar(char c){
	write(1, &c, 1);
}

int main(int argc, char *argv[]){
	int i;
	int j;

	i = argc - 1;
	while (i > 0)
	{
		j = 0;
		while (argv[i][j])
		{
			ft_putchar(argv[i][j]);
			j++;
		}
		ft_putchar('\n');
		--i;
	}

	return (0);
}*/


void ft_putstr(char *str){
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

int main(int argc, char *argv[]){
	while (--argc)
		ft_putstr(argv[argc]);

	
}



