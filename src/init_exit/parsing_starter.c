/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing_starter.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 20:04:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/20 20:55:18 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>
#include <fcntl.h>

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

void	parse_map(t_exit_data *exit_data)
{
	t_map	*map;
	int		max_min_z[2];
	int		error_check;

	map = ft_calloc(1, sizeof(t_map));
	if (!map)
		error_exit(exit_data, MALLOC_ERR, 0);
	map->max_x = -1;
	map->max_y = 0;
	exit_data->fdf->map = map;
	error_check = read_map(map, exit_data->map_fd, 0, exit_data);
	ft_printf("error_cehck: %d\n", error_check);
	ft_printf("map colors: %s\n", map->colors);
	ft_printf("map coord: %s\n", map->coord);
	if (error_check != 0 || map->colors == NULL || map->coord == NULL)
	{	
		ft_printf("eh?\n");
		error_exit(exit_data, PARSE_ERR, 0);
	}
	get_max_min_z(map->coord, max_min_z, map->max_x, map->max_y);
	map->min_z = max_min_z[0];
	map->max_z = max_min_z[1];
	close(exit_data->map_fd);
	exit_data->map_fd = -1;
}
