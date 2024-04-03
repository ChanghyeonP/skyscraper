
// puzzle size - N x N
#define N 4
// data type - box_info[idx]
#define ROW 0
#define COL 1
#define HEIGHT 2
// directions - inputs[idx]
#define UP 0
#define DOWN 1
#define LEFT 2
#define RIGHT 3

int		is_valid_view(int direction, int box_info[3], int puzzle[N][N],
			int inputs[4][N]);
int		get_input_number(int direction, int box_info[3], int inputs[4][N]);
int		*get_boxes_by_direction(int dest_boxes_row[N], int direction,
			int box_info[3], int puzzle[N][N]);
int		count_visible_boxes(int boxes_row[N]);

// Check if the box can be placed at the current location
int	is_valid(int box_info[3], int puzzle[N][N], int inputs[4][N])
{
	int	row;
	int	col;
	int	height;
	int	i;

	row = box_info[ROW];
	col = box_info[COL];
	height = box_info[HEIGHT];
	i = 0;
	while (i < N)
		if (puzzle[i++][col] == height)
			return (0);
	i = 0;
	while (i < N)
		if (puzzle[row][i++] == height)
			return (0);
	if (col == N - 1)
		if (!is_valid_view(LEFT, box_info, puzzle, inputs)
			|| !is_valid_view(RIGHT, box_info, puzzle, inputs))
			return (0);
	if (row == N - 1)
		if (!is_valid_view(UP, box_info, puzzle, inputs)
			|| !is_valid_view(DOWN, box_info, puzzle, inputs))
			return (0);
	return (1);
}

// Check if the box value is valid at the (top|bottom|left|right) point of view.
int	is_valid_view(int direction, int box_info[3], int puzzle[N][N],
					int inputs[4][N])
{
	int	height;
	int	correct_visible_count;
	int	boxes_by_direction[N];

	height = box_info[HEIGHT];
	correct_visible_count = get_input_number(direction, box_info, inputs);
	get_boxes_by_direction(boxes_by_direction, direction, box_info, puzzle);
	if (direction == UP || direction == LEFT)
		boxes_by_direction[N - 1] = height;
	else if (direction == DOWN || direction == RIGHT)
		boxes_by_direction[0] = height;
	if (count_visible_boxes(boxes_by_direction) == correct_visible_count)
	{
		return (1);
	}
	return (0);
}

// Get the number entered in the (top|bottom|left|right) direction
// from the given box location.
int	get_input_number(int direction, int box_info[3], int inputs[4][N])
{
	int	row;
	int	col;

	row = box_info[ROW];
	col = box_info[COL];
	if (direction == UP || direction == DOWN)
		return (inputs[direction][col]);
	if (direction == LEFT || direction == RIGHT)
		return (inputs[direction][row]);
	return (0);
}

// Bring the boxes viewed from the (top|bottom|left|right) direction in a row.
// About box location
int	*get_boxes_by_direction(int dest_boxes_row[N], int direction,
							int box_info[3], int puzzle[N][N])
{
	int	row;
	int	col;
	int	i;

	row = box_info[ROW];
	col = box_info[COL];
	i = 0;
	while (i < N)
	{
		if (direction == UP)
			dest_boxes_row[i] = puzzle[i][col];
		else if (direction == DOWN)
			dest_boxes_row[i] = puzzle[(N - 1) - i][col];
		else if (direction == LEFT)
			dest_boxes_row[i] = puzzle[row][i];
		else if (direction == RIGHT)
			dest_boxes_row[i] = puzzle[row][(N - 1) - i];
		i++;
	}
	return (dest_boxes_row);
}

// Check how many boxes are visible from the front of the input boxes row
int	count_visible_boxes(int boxes_row[N])
{
	int	i;
	int	visible_count;
	int	max_value;

	i = 0;
	visible_count = 0;
	max_value = 0;
	while (i < N)
	{
		if (max_value < boxes_row[i])
		{
			max_value = boxes_row[i];
			visible_count++;
		}
		i++;
	}
	return (visible_count);
}










