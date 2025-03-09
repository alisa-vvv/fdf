#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// question: use struct for each individual coordinate point? feels wrong.
// alternative: use a single 3d array. then points can be found by coordinates.
// question: what is x=0? what is y=0? is it the top of the map?
// probably, feels the easiest since it's the order in which string is read.
// left to right, up to down
//

void	free_string_array(char **arr)
{
	int	i;

	if (arr)
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

int	*funny_recursive_allocate_x(int *coord, char **values, int x, int *max_x)
{
	if (values[x])
		coord = funny_recursive_allocate_x(coord, values, x + 1, max_x);
	else
	{
		coord = (int *) malloc(sizeof(int) * x);
		if (!coord)
			return (NULL);
		*max_x = x - 1;
		return (coord);
	}
	coord[x] = ft_atoi(values[x]);
	return (coord);
}

int	get_x_z(int **coord, char *line)
{
	char	**values;
	int		max_x;

	values = ft_split(line, ' ');
	if (!values)
	{
		perror(MALLOC_ERR);
		// ADD ERROR MANAGEMENT
		coord = NULL;
	}
	max_x = 0;
	*coord = funny_recursive_allocate_x(*coord, values, 0, &max_x);
	free_string_array(values);
	return (max_x);
}

int	**funny_recursive_map_read(int map_fd, int *y, int *max_x)
{
	char	*next_line;
	int		**coord;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
	{
		(*y)++;
		coord = funny_recursive_map_read(map_fd, y, max_x);
	}
	else
	{
		coord = (int **) malloc((*y + 1) * sizeof(int *));
		coord[*y] = NULL;
		*y = 0;
		return (coord);
	}
	*max_x = get_x_z(&coord[*y], next_line);
	(*y)++;
	free(next_line);
	return (coord);
}

void	test_recursive_print_map(int **coord, int y, int max_x)
{
	int	x;

	while (y--)
	{
		x = 0;
		while(x <= max_x)
		{
			ft_printf("%d ", coord[y][x]);
			ft_putchar_fd(' ', STDOUT_FILENO);
			x++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	free_coord(int **coord)
{
	int	y;

	y = -1;
	while (coord[++y])
		free(coord[y]);
	free(coord);
}

void	parse_map(char *filename)
{
	const int	map_fd = open(filename, O_RDONLY);
	int			y;
	int			**coord;
	int			max_x;

	y = 0;
	coord = funny_recursive_map_read(map_fd, &y, &max_x);
	test_recursive_print_map(coord, y, max_x);
	free_coord(coord);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	parse_map(argv[1]);
	return (0);
}
