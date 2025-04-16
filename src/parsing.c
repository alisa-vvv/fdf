/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/16 20:46:42 by avaliull     ########   odam.nl          */
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
		coord = NULL;
		return (-1);
	}
	max_x = 0;
	*coord = allocate_x(*coord, values, 0, &max_x);
	free_2d_arr((void **) values);
	return (max_x);
}

static void	read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data)
{
	char	*next_line;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
		read_map(map, map_fd, y + 1, exit_data);
	else
	{
		map->coord = (int **) ft_calloc((y + 1), sizeof(int *));
		map->max_y = y - 1;
		return ;
	}
	map->max_x = get_x_z(&map->coord[y], next_line);
	if (map->coord == NULL)
		error_exit(exit_data, MALLOC_ERR, false);
	free(next_line);
}

void	parse_colors(t_map *map, t_exit_data *exit_data, int fd)
{
	char	***color_map;
	char	**cell_value;
	char	*next_line;
	int		x;
	int		y;

	color_map = ft_calloc(map->max_y + 1, sizeof(char **));
	map->colors = color_map;
	if (!color_map)
		error_exit(exit_data, MALLOC_ERR, false);
	y = -1;
	while (++y <= map->max_y)
	{
		next_line = ft_calloc(map->max_x + 1, sizeof(char *));
		if (!next_line)
		{
			error_exit(exit_data, MALLOC_ERR, false);
		}
		x = -1;
		read(fd, next_line, map->max_x + 1);
		ft_printf("next_line: %d\n", next_line);
		while (++x <= map->max_x)
		{
			cell_value = ft_split(next_line, ',');
			if (!cell_value)
			{
				free(next_line);
				error_exit(exit_data, MALLOC_ERR, false);
			}
			if (cell_value[1] != NULL)
				color_map[y][x] = ft_strdup(cell_value[1]);
			else
				color_map[y][x] = ft_strdup("0xFFFFFFFF");
			ft_printf("where?\n");
			if (!color_map[y][x])
			{
				free(next_line);
				free_2d_arr((void **) cell_value);
				error_exit(exit_data, MALLOC_ERR, false);
			}
		}
	}
}

t_map	parse_map(t_exit_data *exit_data, char *name)
{
	t_map		map;
	int			max_min_z[2];

	map.max_y = 0;
	map.max_x = 0;
	map.max_z = 0;
	map.min_z = 0;
	map.colors = NULL;
	// this is how bloatware is created
	read_map(&map, exit_data->map_fd, 0, exit_data);
	get_max_min_z(map.coord, max_min_z, map.max_x, map.max_y);
	map.min_z = max_min_z[0];
	map.max_z = max_min_z[1];
	close(exit_data->map_fd);
	exit_data->map_fd = open(name, O_RDONLY);
	parse_colors(&map, exit_data, exit_data->map_fd);
	close(exit_data->map_fd);
	return (map);
}

