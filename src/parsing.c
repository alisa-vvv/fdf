/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/09 20:06:47 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <fcntl.h>

static int	*funny_recursive_allocate_x(int *coord, char **values, int x, int *max_x)
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
	*coord = funny_recursive_allocate_x(*coord, values, 0, &max_x);
	free_2d_arr((void **) values);
	return (max_x);
}

static int	**funny_recursive_map_read(int map_fd, int y, int *max_x, int *max_y)
{
	char	*next_line;
	int		**coord;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
		coord = funny_recursive_map_read(map_fd, y + 1, max_x, max_y);
	else
	{
		coord = (int **) malloc((y + 1) * sizeof(int *));
		coord[y] = NULL;
		*max_y = y;
		return (coord);
	}
	*max_x = get_x_z(&coord[y], next_line);
	free(next_line);
	return (coord);
}

t_map	parse_map(char *filename)
{
	const int	map_fd = open(filename, O_RDONLY);
	int			**coord;
	t_map		map;

	map.max_y = 0;
	map.max_x = 0;
	// this is how bloatware is created
	coord = funny_recursive_map_read(map_fd, 0, &(map.max_x), &(map.max_y));
	map.max_y--;
	map.coord = coord;
	close(map_fd);
	return (map);
}

