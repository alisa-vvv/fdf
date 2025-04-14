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
#include <errno.h>

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
	coord = funny_recursive_map_read(map_fd, 0, &(map.max_x), &(map.max_y));
	map.coord = coord;
	get_max_min_z(coord, max_min_z, map.max_x, map.max_y);
	map.min_z = max_min_z[0];
	map.max_z = max_min_z[1];
	close(map_fd);
	return (map);
}

