#include <unistd.h>

// puzzle size - N x N
#define N 4
// data type - box_info[idx]
#define ROW 0
#define COL 1
#define HEIGHT 2

int		is_valid(int box_info[3], int puzzle[N][N], int inputs[4][N]);

// Initialize array values to 0; same.. puzzle[N][N] = {0};
void	init_puzzle(int puzzle[N][N])
{
	int	i;
	int	j;

	i = 0;
	while (i < N)
	{
		j = 0;
		while (j < N)
		{
			puzzle[i][j] = 0;
			j++;
		}
		i++;
	}
} // 배열 안의 원소 0으로 초기화

// print the N x N puzzle
void	print_puzzle(int puzzle[N][N])
{
	int		i;
	int		j;
	char	c;

	i = 0;
	while (i < N)
	{
		j = 0;
		while (j < N)
		{
			c = puzzle[i][j] + '0';
			write(1, &c, 1);
			if (j < N - 1)
				write(1, " ", 1);
			j++;
		}
		write(1, "\n", 1);
		i++;
	}
} // 출력 틀 생성

// Solve puzzle using backtracking method
int	solve_puzzle(int row, int col, int puzzle[N][N], int inputs[4][N])
{
	int	box_info[3];
	int	height;

	if (row == N)
		return (1);
	if (col == N)
		return (solve_puzzle(row + 1, 0, puzzle, inputs));
	box_info[ROW] = row;
	box_info[COL] = col;
	height = 1;
	while (height <= N)
	{
		box_info[HEIGHT] = height;
		if (is_valid(box_info, puzzle, inputs))
		{
			puzzle[row][col] = height;
			if (solve_puzzle(row, col + 1, puzzle, inputs))
				return (1);
			else
				puzzle[row][col] = 0;
		}
		height++;
	}
	return (0);
}
