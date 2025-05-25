/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing_loop.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/20 19:43:20 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/20 20:53:41 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>

int	read_colors(char **values, char **colors, const int x)
{
	char	**color_check;

	if (values[x])
	{
		color_check = ft_split(values[x], ',');
		if (!color_check)
			return (1);
		if (color_check[1] == NULL)
			colors[x] = ft_strdup(COLOR_TEAL);
		else
			colors[x] = color_check[1];
		free_2d_arr((void **) color_check);
	}
	else
		colors[x] = ft_strdup(COLOR_TEAL);
	if (!colors[x])
		return (1);
	return (0);
}

static int	allocate_x(char **values, int *coord,
					  char **colors, const int max_x)
{
	int	x;
	int	error_check;

	error_check = 0;
	x = max_x;
	while (x >= 0)
	{
		if (values[x])
			coord[x] = ft_atoi(values[x]);
		error_check = read_colors(values, colors, x);
		if (error_check != 0)
			break ;
		x--;
	}
	return (error_check);
}

static int	get_x_z(t_map *map, int **coord, char *line, int y)
{
	char	**values;
	int		error_check;

	error_check = 0;
	values = ft_split(line, ' ');
	if (!values)
		return (1);
	*coord = (int *) ft_calloc(map->max_x + 1, sizeof(int));
	if (!coord)
	{
		free_2d_arr((void **) values);
		return (1);
	}
	map->colors[y] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
	if (!map->colors[y])
	{
		free_2d_arr((void **) values);
		return (1);
	}
	error_check = allocate_x(values, *coord, map->colors[y], map->max_x);
		free_2d_arr((void **) values);
	return (error_check);
}

static int	panic_free(int **coord, char ***colors, int y)
{
	int	i;
	int	x;

	i = y;
	if (coord)
	{
		while (coord[i])
		{
			free(coord[i]);
			coord[i++] = NULL;
		}
	}
	i = y;
	if (colors)
	{
		while (colors[i])
		{
			x = -1;
			while (colors[i][++x])
				free(colors[i][x]);
			free(colors[i]);
			colors[i++] = NULL;
		}
	}
	return (1);
}

int	read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data)
{
	int			err_check;
	char		*const next_line = get_next_line(exit_data->map_fd);

	err_check = 0;
	if (next_line != NULL && y < MAX_MAP_SIZE)
		err_check = read_map(map, map_fd, y + 1, exit_data);
	else
	{
		if (next_line)
			free(next_line);
		if (y == 0 || y >= MAX_MAP_SIZE || err_check != 0)
		{
			return (1);
		}
		map->coord = (int **) ft_calloc((y + 1), sizeof(int *));
		map->colors = (char ***) ft_calloc((y + 1), sizeof(char **));
		if (!map->coord || !map->colors)
		{
			return (1);
		}
		map->max_y = y - 1;
		return (0);
	}
	if (err_check != 1)
	{
		err_check = get_x_z(map, &map->coord[y], next_line, y);
	}
	if (err_check != 0)
	{
		err_check = panic_free(map->coord, map->colors, y + 1);
	}
	return (free(next_line), err_check);
}
