#include <unistd.h>
#include <stdio.h>

/*void ft_putchar(char c){
	write(1, &c, 1);
}

int main(int argc, char *argv[]){
	int i;
	int j;

	(void)argc;

	i = 1;
	while (argv[i] != NULL) // this is diff from '\0'.
	{
		j = 0;
		while (argv[i][j])
		{
			ft_putchar(argv[i][j]);
			j++;
		}
		ft_putchar('\n');
		i++;
	}

	return (0);
}*/

//Another Solution//

void ft_putsrt(char *str){
	while (*str)
		write(1, str++, 1);
	write(1, "\n", 1);
}

int main(int argc, char *argv[]){
	(void)argc;
	while (*(++argv))
		ft_putsrt(*argv);
}
