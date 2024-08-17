#include <unistd.h>
#include <stdlib.h>

void	ft_putstr(char *str)
{
	while (*str)
		write(1, str++, 1);
}

void	ft_puterror(void)
{
	ft_putstr("Error\n");
	exit(1);
}

int		is_valid(int grid[4][4], int row, int col, int num)
{
	int i;

	// Check if num is already in the row or column
	for (i = 0; i < 4; i++)
		if (grid[row][i] == num || grid[i][col] == num)
			return (0);
	return (1);
}

// A utility function to print grid
void	print_grid(int grid[4][4])
{
	int i;
	int j;
	char c;

	for (i = 0; i < 4; i++)
	{
		for (j = 0; j < 4; j++)
		{
			c = grid[i][j] + '0';
			write(1, &c, 1);
			if (j < 3)
				write(1, " ", 1);
		}
		write(1, "\n", 1);
	}
}

int		check_constraints(int grid[4][4], int *constraints)
{
	int row, col, max, visible;

	// Check columns (up and down views)
	for (col = 0; col < 4; col++)
	{
		max = 0;
		visible = 0;
		for (row = 0; row < 4; row++)
			if (grid[row][col] > max)
			{
				max = grid[row][col];
				visible++;
			}
		if (visible != constraints[col])
			return (0);
		max = 0;
		visible = 0;
		for (row = 3; row >= 0; row--)
			if (grid[row][col] > max)
			{
				max = grid[row][col];
				visible++;
			}
		if (visible != constraints[col + 4])
			return (0);
	}

	// Check rows (left and right views)
	for (row = 0; row < 4; row++)
	{
		max = 0;
		visible = 0;
		for (col = 0; col < 4; col++)
			if (grid[row][col] > max)
			{
				max = grid[row][col];
				visible++;
			}
		if (visible != constraints[row + 8])
			return (0);
		max = 0;
		visible = 0;
		for (col = 3; col >= 0; col--)
			if (grid[row][col] > max)
			{
				max = grid[row][col];
				visible++;
			}
		if (visible != constraints[row + 12])
			return (0);
	}

	return (1);
}

int		solve(int grid[4][4], int *constraints, int pos)
{
	int row;
	int col;
	int num;

	if (pos == 16)
		return (check_constraints(grid, constraints));
	row = pos / 4;
	col = pos % 4;
	for (num = 1; num <= 4; num++)
	{
		if (is_valid(grid, row, col, num))
		{
			grid[row][col] = num;
			if (solve(grid, constraints, pos + 1))
				return (1);
			grid[row][col] = 0;
		}
	}
	return (0);
}

int		*parse_input(char *input)
{
	int i;
	int *constraints;

	constraints = (int *)malloc(16 * sizeof(int));
	if (!constraints)
		ft_puterror();
	i = 0;
	while (i < 16)
	{
		if (input[i * 2] < '1' || input[i * 2] > '4' || (input[i * 2 + 1] != ' ' && input[i * 2 + 1] != '\0'))
			ft_puterror();
		constraints[i] = input[i * 2] - '0';
		i++;
	}
	return (constraints);
}

int		main(int argc, char **argv)
{
	int grid[4][4] = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
	int *constraints;

	if (argc != 2)
		ft_puterror();
	constraints = parse_input(argv[1]);
	if (solve(grid, constraints, 0))
		print_grid(grid);
	else
		ft_puterror();
	free(constraints);
	return (0);
}
