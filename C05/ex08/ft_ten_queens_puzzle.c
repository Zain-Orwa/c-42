#include <unistd.h>
#include <stdio.h>

void ft_putchar(char c){
	write(1, &c, 1);
}

void print_solutiion(int *board){
	int i;

	i = 0;
	while (i < 10){
		ft_putchar(board[i] + '0');
		i++;
	}
	ft_putchar('\n');
}

int ft_abs(int num){
	if (num < 0)
		return (-num);
	return (num);
}

int is_safe(int *board, int col, int row){
	int i;
	int row_diff;
	int col_diff;

	i = 0;
	while (i < col){
		if (board[i] == row)
			return (0);
		row_diff = ft_abs(board[i] - row);
		col_diff = col - i;
		if (row_diff == col_diff)
			return (0);
		i++;
	}
	return (1);
}

void ft_backtrack(int *board, int col, int *solutions){
	int row;

	if (col == 10)
	{
		print_solutiion(board);
		*solutions = *solutions + 1;
	}

	row = 0;
	while (row < 10)
	{
		if (is_safe(board, col, row))
		{
			board[col] = row;
			ft_backtrack(board, col + 1, solutions);
		}
		row++;
	}
}

int ft_ten_queens_puzzle(void){
	int board[10];
	int solutions;

	solutions = 0;
	ft_backtrack(board, 0, &solutions);

	return (solutions);
}

int main(){
	int count = 0;

	count = ft_ten_queens_puzzle();
	printf("Total Solution Are: %d\n", count);


	return (0);
}
