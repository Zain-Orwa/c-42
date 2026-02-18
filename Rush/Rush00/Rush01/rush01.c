#define CELL_TOP_LEFT         0
#define CELL_TOP_RIGHT        1
#define CELL_BOTTOM_LEFT      2
#define CELL_BOTTOM_RIGHT     3
#define CELL_HORIZONTAL_EDGE  4
#define CELL_VERTICAL_EDGE    5
#define CELL_INSIDE           6

void	ft_putchar(char c);

static int	identify_cell_type(int current_row, int current_col, int width, int height)
{
	if (current_row == 1 && current_col == 1)
		return (CELL_TOP_LEFT);
	if (current_row == 1 && current_col == width)
		return (CELL_TOP_RIGHT);
	if (current_row == height && current_col == 1)
		return (CELL_BOTTOM_LEFT);
	if (current_row == height && current_col == width)
		return (CELL_BOTTOM_RIGHT);
	if (current_row == 1 || current_row == height)
		return (CELL_HORIZONTAL_EDGE);
	if (current_col == 1 || current_col == width)
		return (CELL_VERTICAL_EDGE);
	return (CELL_INSIDE);
}

char	get_cell_char(int cell_type)
{
	if (cell_type == CELL_TOP_LEFT || cell_type == CELL_BOTTOM_RIGHT)
		return ('/');
	if (cell_type == CELL_TOP_RIGHT || cell_type == CELL_BOTTOM_LEFT)
		return ('\\');
	if (cell_type == CELL_HORIZONTAL_EDGE || cell_type == CELL_VERTICAL_EDGE)
		return ('*');
	return (' ');
}


/*
** IMPORTANT: subject expects rush(x, y)
** x = width (columns), y = height (rows)
*/
void	rush(int x, int y){
	int		width;
	int		height;
	int		current_row;
	int		current_col;
	int		cell_type;
	char	cell_char;

	width = x;
	height = y;
	if (width <= 0 || height <= 0)
		return ;

	current_row = 1;
	while (current_row <= height)
	{
		current_col = 1;
		while (current_col <= width)
		{
			cell_type = identify_cell_type(current_row, current_col, width, height);
			cell_char = get_cell_char(cell_type);
			ft_putchar(cell_char);
			current_col++;
		}
		ft_putchar('\n');
		current_row++;
	}
}

