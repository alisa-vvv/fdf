/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing_starter.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/22 22:09:16 by avaliull     ########   odam.nl          */
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

void	get_first_line(t_map *map, t_exit_data *exit_data)
{
	char	*first_line;
	char	**split_line;
	int		error_check;
	int		len;
	int		x;

	first_line = get_next_line(exit_data->map_fd);
	ft_printf("first_line: %s\n", first_line);
	if (!first_line)
		error_exit(exit_data, MALLOC_ERR, 0);
	split_line = ft_split(first_line, ' ');
	if (!split_line)
		error_exit(exit_data, MALLOC_ERR, 0);
	ft_printf("zero zero: %s\n", split_line[0][0]);
	int y = -1;
	while (split_line[++y])
	{
		ft_printf("haty\n");
		int x = -1;
		while (split_line[y][++x])
			ft_printf("split line: %s\n", split_line[y][x]);
	}
	ft_printf("WHERE\n");
	len = 0;
	while (split_line[len])
		len++;
	map->max_x = len - 1;
	// this will be moved to init
	map->coord = (int **) ft_calloc(128, sizeof(int *));
	map->colors = (char ***) ft_calloc(128, sizeof(char **));
	if (!map->coord || !map->colors)
		error_exit(exit_data, MALLOC_ERR, 0);
	// this will be moved to init
	x = -1;
	while (++x <= map->max_x)
	{
		map->coord[0][x] = ft_atoi(split_line[x]);
		error_check = read_colors(split_line, map->colors[0], map->max_x);
		if (error_check != 0)
			error_exit(exit_data, MALLOC_ERR, 0);
	}
}

//void	initial_read(t_map *map, t_exit_data *exit_data, char **first_line)
//{
//	int	map_y;
//	int	y;
//
//	map_y = 128;
//	y = 0;
//	while (++y < map_y)
//	{
//		
//	}
//}

void	parse_map(t_exit_data *exit_data)
{
	t_map	*map;
	int		max_min_z[2];
	//int		error_check;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_exit(exit_data, MALLOC_ERR, 0);
	map->max_x = 0;
	map->max_y = 0;
	exit_data->fdf->map = map;
	get_first_line(map, exit_data);
	test_print_map(map->coord, map->max_x, 127);
	//error_check = read_map(map, exit_data->map_fd, 0, exit_data);
//	if (error_check != 0 || map->colors == NULL || map->coord == NULL)
//		error_exit(exit_data, PARSE_ERR, 0);
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
