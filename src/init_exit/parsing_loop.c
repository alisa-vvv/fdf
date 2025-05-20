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

static int	read_colors(char **values, char **colors, int max_x)
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

static int	*allocate_x(int *coord, char **values, int x, int *max_x)
{
	if (values[x])
		coord = allocate_x(coord, values, x + 1, max_x);
	else
	{
		coord = (int *) ft_calloc(x, sizeof(int));
		if (!coord)
			return (NULL);
		//ft_printf("x: %d\n", x);
		//ft_printf("max_x: %d\n", *max_x);
		if (*max_x == x - 1 || *max_x == -1)
		{
			*max_x = x;
			//ft_printf("do we get here?\n");
		}
		else
		{
		//	ft_printf("do we get here?  2\n");
			*max_x = -2;
		}
		return (coord);
	}
	if (coord)
		coord[x] = ft_atoi(values[x]);
	return (coord);
}

static int	get_x_z(t_map *map, int **coord, char *line, int y)
{
	char	**values;

	values = ft_split(line, ' ');
	if (!values)
		return (-1);
	*coord = allocate_x(*coord, values, 0, &map->max_x);
	if (!*coord || map->max_x == -2)
	{
		ft_printf("why ? i cry\n");
		free_2d_arr((void **) values);
		return (-1);
	}
	map->max_x--;
	map->colors[y] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
	if (!map->colors[y])
	{
		free_2d_arr((void **) values);
		return (-1);
	}
	if (read_colors(values, map->colors[y], map->max_x) != 0)
	{
		map->max_x = -1;
	}
	free_2d_arr((void **) values);
	return (map->max_x);
}

static int	panic_free(int **coord, char ***colors, int y)
{
	int	i;
	i = y;
	if (coord)
		while (coord[i])
			free(coord[i++]);
	i = y;
	if (colors)
		while (colors[i])
			free(colors[i++]);
	return (1);
}

int	read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data)
{
	char	*next_line;
	int		err_check;

	next_line = get_next_line(map_fd);
	if (next_line != NULL)
		err_check = read_map(map, map_fd, y + 1, exit_data);
	else
	{
		map->coord = (int **) ft_calloc((y + 1), sizeof(int *));
		map->colors = (char ***) ft_calloc((y + 1), sizeof(char **));
		if (!map->coord || !map->colors)
			return (1);
		map->max_y = y - 1;
		return (0);
	}
	if (err_check != 1)
		map->max_x = get_x_z(map, &map->coord[y], next_line, y);
	if (map->max_x < 0 || err_check != 0)
		err_check = panic_free(map->coord, map->colors, y);
	free(next_line);
	return (err_check);
}
