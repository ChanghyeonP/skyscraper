#include <unistd.h>

// puzzle size - N x N
#define N 4

void	init_puzzle(int puzzle[N][N]);
void	print_puzzle(int puzzle[N][N]);
int		solve_puzzle(int row, int col, int puzzle[N][N], int inputs[4][N]);
int		init_inputs(int dest_inputs[4][N], int argc, char **argv);
int		valid_input_length(char *input_str);
int		valid_input_patten(char *input_str);
void	set_inputs_from_str(int inputs[4][N], char	*input_str);

/*
int main(int argc, char *argv[])

	argc : argument count (argv[0] -1)
	argv : argument variable array (string)

	argv[0] : program location
	argv[1] : input string
*/
int	main(int argc, char **argv)
{
	int	puzzle[N][N];
	int	inputs[4][N];

	init_puzzle(puzzle);
	if (init_inputs(inputs, argc, argv) != 1)
	{
		write(1, "Error\n", 6);
	}
	else if (solve_puzzle(0, 0, puzzle, inputs))
	{
		print_puzzle(puzzle);
	}
	else
	{
		write(1, "Error\n", 6);
	}
	return (0);
}

/*
initial inputs[4][N] from input string
	with error check

	* error check case 3

		case -1 : not 2 argument count
		case -2 : invalid input string length
		case -3 : invalid input string patten

	return 1 is Initialization complete
*/
int	init_inputs(int dest_inputs[4][N], int argc, char **argv)
{
	if (argc != 2)
		return (-1);
	else if (!valid_input_length(argv[1]))
		return (-2);
	else if (!valid_input_patten(argv[1]))
		return (-3);
	else
	{
		set_inputs_from_str(dest_inputs, argv[1]);
		return (1);
	}
}

// processing string length (number == N * 4, space == number - 1)
int	valid_input_length(char *input_str)
{
	int	str_idx;

	str_idx = 0;
	while (input_str[str_idx] != '\0')
		str_idx++;
	if (str_idx != (((N * 4) * 2) - 1))
		return (0);
	else
		return (1);
}

// processing string pattern
int	valid_input_patten(char *input_str)
{
	int	str_idx;

	str_idx = 0;
	while (input_str[str_idx] != '\0')
	{
		if ((str_idx % 2) == 0)
		{
			if (!('1' <= input_str[str_idx] && input_str[str_idx] <= '0' + N))
				return (0);
		}
		else
		{
			if (!(input_str[str_idx] == ' '))
				return (0);
		}
		str_idx++;
	}
	return (1);
}

// initialize inputs[4][N] with a string
void	set_inputs_from_str(int inputs[4][N], char	*input_str)
{
	int		str_idx;
	int		i;
	int		j;

	str_idx = 0;
	i = 0;
	j = 0;
	while (i < 4)
	{
		while (j < (N * 2) && input_str[str_idx] != '\0')
		{
			if ((str_idx % 2) == 0
				&& ('1' <= input_str[str_idx] && input_str[str_idx] <= '0' + N))
			{
				inputs[i][j / 2] = input_str[str_idx] - '0';
			}
			j++;
			str_idx++;
		}
		j = 0;
		i++;
	}
}
