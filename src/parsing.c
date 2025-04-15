/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 16:49:11 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <fcntl.h>

void	get_max_min_z(int **coord, int *max_min_z,
					const int max_x, const int max_y)
{
	int	x;
	int	y;
	int	max_z;
	int	min_z;

	max_z = coord[0][0];
	min_z = coord[0][0];
	y = -1;
	while (++y <= max_y)
	{
		x = -1;
		while(++x <= max_x)
		{
			if (coord[y][x] > max_z)
				max_z = coord[y][x];
			if (coord[y][x] < min_z)
				min_z = coord[y][x];
		}
	}
	max_min_z[0] = min_z;
	max_min_z[1] = max_z;
}

static int	*allocate_x(int *coord, char **values, int x, int *max_x)
{
	if (values[x])
		coord = allocate_x(coord, values, x + 1, max_x);
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

// here, should add a variablke called char **color_map
// then using ft_split we can see if there's a color variable in the cell
// then save it to color map
// color map can then be either merged with the regular map or exist on it's won
// it's the same size and has the same indexes as the regular map so I can iterate through it whenever I iterate through the map
// I don't remember if any of the functions I have can convert from hex string to int, but it shouldn't be hard to make.
// then those values can be added to vectors and used for color grading the image
// profit

static int	get_x_z(int **coord, char *line)
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
	*coord = allocate_x(*coord, values, 0, &max_x);
	free_2d_arr((void **) values);
	return (max_x);
}

static int	**read_map(int map_fd, int y, int *max_x, int *max_y)
{
	char	*next_line;
	int		**coord;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
		coord = read_map(map_fd, y + 1, max_x, max_y);
	else
	{
		coord = (int **) malloc((y + 1) * sizeof(int *));
		coord[y] = NULL;
		*max_y = y - 1;
		return (coord);
	}
	*max_x = get_x_z(&coord[y], next_line);
	free(next_line);
	return (coord);
}

t_map	parse_map(const int map_fd)
{
	int			**coord;
	t_map		map;
	int			max_min_z[2];

	map.max_y = 0;
	map.max_x = 0;
	map.max_z = 0;
	map.min_z = 0;
	// this is how bloatware is created
	coord = read_map(map_fd, 0, &(map.max_x), &(map.max_y));
	map.coord = coord;
	get_max_min_z(coord, max_min_z, map.max_x, map.max_y);
	map.min_z = max_min_z[0];
	map.max_z = max_min_z[1];
	close(map_fd);
	return (map);
}

