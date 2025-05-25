/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing_starter.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/25 17:08:13 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <fcntl.h>

static void	to_hex(uint32_t n, char *color_str)
{
	int			i;
	const char	symbols[17] = "0123456789ABCDEF";

	i = 10;
	color_str[0] = '0';
	color_str[1] = 'x';
	color_str[i] = '\0';
	ft_memset(&color_str[2], '0', 8);
	while (n)
	{
		i--;
		color_str[i] = symbols[n % 16];
		n /= 16;
	}
}

void	construct_height_color_map(t_map *map, char ***colors, int **coord)
{
	int		y;
	int		x;
	int		inc;

	y = -1;
	while (++y <= map->max_y)
	{
		x = -1;
		while (++x <= map->max_x)
		{
			if (map->coord[y][x] > 0)
			{
				inc = 255 * coord[y][x] / map->max_z;
				to_hex((inc << 24) + ((255 - inc) << 16) + 255, colors[y][x]);
			}
			else if (map->coord[y][x] < 0)
			{
				inc = 255 * coord[y][x] / map->min_z;
				to_hex((inc << 8) + ((255 - inc) << 16) + 255, colors[y][x]);
			}
			else
				colors[y][x] = ft_memcpy(colors[y][x], COLOR_GREEN, 10);
		}
	}
}

static void	get_max_min_z(int **const coord, int *max_min_z,
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
		while (++x <= max_x)
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

static void	alloc_height_color_map(t_map *map, char ***colors,
									t_exit_data *exit_data)
{
	int	y;
	int	x;

	y = -1;
	while (++y <= map->max_y)
	{
		colors[y] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
		if (!colors[y])
			error_exit(exit_data, MALLOC_ERR, 0);
		x = -1;
		while (++x <= map->max_x)
		{
			colors[y][x] = (char *) ft_calloc(11, sizeof(char));
			if (!colors[y][x])
				error_exit(exit_data, MALLOC_ERR, 0);
		}
	}
}

char	**read_first_line(t_map *map, int map_fd, t_exit_data *exit_data)
{
	char	*first_line;
	char	*cleaned_line;
	char	**split_line;

	first_line = get_next_line(map_fd);
	if (!first_line)
		error_exit(exit_data, MALLOC_ERR, false);
	cleaned_line = ft_strtrim(first_line, "\n");
	free(first_line);
	if (!cleaned_line)
		error_exit(exit_data, MALLOC_ERR, false);
	split_line = ft_split(cleaned_line, ' ');
	free(cleaned_line);
	if (!split_line)
		error_exit(exit_data, MALLOC_ERR, false);
	while (split_line[map->max_x])
		map->max_x++;
	map->max_x--;
	if (map->max_x >= MAX_MAP_SIZE)
	{
		free_2d_arr((void **) split_line);
		error_exit(exit_data, BIG_MAP_ERR, false);
	}
	return (split_line);
}

void	add_first_line(char **first_line, t_map *map, t_exit_data *exit_data)
{
	int	x;

	map->coord[0] = (int *) ft_calloc(map->max_x + 1, sizeof(int));
	if (!map->coord[0])
	{
		free_2d_arr((void **) first_line);
		error_exit(exit_data, MALLOC_ERR, false);
	}
	x = map->max_x;
	while (x)
	{
		map->coord[0][x] = ft_atoi(first_line[x]);
		x--;
	}
	map->colors[0] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
	if (!map->colors[0])
	{
		free_2d_arr((void **) first_line);
		error_exit(exit_data, MALLOC_ERR, false);
	}
	read_colors(first_line, map->colors[0], map->max_x);
	free_2d_arr((void **) first_line);
	if (!map->colors[1])
		error_exit(exit_data, MALLOC_ERR, false);
}

void	parse_map(t_exit_data *exit_data)
{
	t_map	*map;
	int		max_min_z[2];
	int		error_check;
	char	**first_line;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_exit(exit_data, MALLOC_ERR, false);
	map->max_x = 0;
	map->max_y = 0;
	exit_data->fdf->map = map;
	first_line = read_first_line(map, exit_data->map_fd, exit_data);
	error_check = read_map(map, exit_data->map_fd, 1, exit_data);
	if (error_check != 0 || map->colors == NULL || map->coord == NULL)
		error_exit(exit_data, PARSE_ERR, 0);
	add_first_line(first_line, map, exit_data);
	get_max_min_z(map->coord, max_min_z, map->max_x, map->max_y);
	map->min_z = max_min_z[0];
	map->max_z = max_min_z[1];
	map->height_colors = (char ***) ft_calloc(map->max_y + 2, sizeof(char **));
	if (!map->height_colors)
		error_exit(exit_data, MALLOC_ERR, 0);
	alloc_height_color_map(map, map->height_colors, exit_data);
	construct_height_color_map(map, map->height_colors, map->coord);
	close(exit_data->map_fd);
	exit_data->map_fd = -1;
}
