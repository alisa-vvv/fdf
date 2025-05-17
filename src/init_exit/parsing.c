/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing.c                                         :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/08 19:22:32 by avaliull     ########   odam.nl          */
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

// can I shove the colors here?
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

int		read_colors(char **values, char **colors, int max_x)
{
	int		x;
	char	**color_check;

	x = -1;
	while (++x <= max_x)
	{
		color_check = ft_split(values[x], ',');
		if (!color_check)
			return (1);
		if (color_check[1] == NULL)
		{
			colors[x] = ft_strdup(COLOR_WHITE);
			if (!colors[x])
			{
				free_2d_arr((void **) color_check);
				return (1);
			}
		}
		else
			colors[x] = color_check[1];
		free(color_check[0]);
		free(color_check);
	}
	return (0);
}

static int	get_x_z(int **coord, char ***colors, char *line, int y)
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
	if (!*coord)
	{
		free_2d_arr((void **) values);
		return (-1);
	}
	colors[y] = (char **) ft_calloc(max_x + 2, sizeof(char *));
	if (read_colors(values, colors[y], max_x) != 0)
		colors = NULL;
	free_2d_arr((void **) values);
	return (max_x);
}

static int	read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data)
{
	char	*next_line;
	int		err_check;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
		err_check = read_map(map, map_fd, y + 1, exit_data);
	else
	{
		map->coord = (int **) ft_calloc((y + 1), sizeof(int *));
		if (!map->coord)
			return (1);
		map->colors = (char ***) fake_ft_calloc((y + 1), sizeof(char **));
		if (!map->colors)
			return (1);
		map->max_y = y - 1;
		return (0);
	}
	if (err_check != 1)
	{
		map->max_x = get_x_z(&map->coord[y], map->colors, next_line, y);
		if (map->max_x <= 0)
			err_check = 1;
	}
	free(next_line);
	return (err_check);
}

void	parse_map(t_exit_data *exit_data)
{
	t_map	*map;
	int		max_min_z[2];
	int		error_check;

//	map.max_y = 0;
//	map.max_x = 0;
//	map.max_z = 0;
//	map.min_z = 0;
//	map.colors = NULL;
//	map.coord = NULL;
	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_exit(exit_data, MALLOC_ERR, 0);
	exit_data->fdf->map = map;
	error_check = read_map(map, exit_data->map_fd, 0, exit_data);
	ft_printf("map.colors: %d, map.coord: %d\n", map->colors, map->coord);
	if (error_check != 0 || map->colors == NULL || map->coord == NULL)
		error_exit(exit_data, PARSE_ERR, 0);
	get_max_min_z(map->coord, max_min_z, map->max_x, map->max_y);
	map->min_z = max_min_z[0];
	map->max_z = max_min_z[1];
	close(exit_data->map_fd);
	exit_data->map_fd = -1;
}

