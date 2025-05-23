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

int	read_colors(char **values, char **colors, int max_x)
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
			colors[x] = ft_strdup("FFC5D3FF");
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

//static int	*allocate_x(int *coord, char **values, int x, int *max_x)
//{
//	if (values[x] && (ft_isdigit(values[x][0]) || ft_issign(values[x][0])))
//		coord = allocate_x(coord, values, x + 1, max_x);
//	else
//	{
//		if (x >= MAX_MAP_SIZE)
//			return (NULL);
//		coord = (int *) ft_calloc(x, sizeof(int));
//		if (!coord)
//			return (NULL);
//		if ((*max_x == x - 1 || *max_x == -1))
//		{
//		//	ft_printf("does this trigger here?\n");
//			*max_x = x;
//		}
//		else
//		{
//			free(coord);
//			return (NULL);
//		}
//		return (coord);
//	}
//	if (coord)
//		coord[x] = ft_atoi(values[x]);
//	return (coord);
//}
//
//static int	get_x_z(t_map *map, int **coord, char *line, int y)
//{
//	char	**values;
//	int		error_check;
//
//	error_check = 0;
//	values = ft_split(line, ' ');
//	if (!values)
//		return (1);
//	*coord = allocate_x(*coord, values, 0, &map->max_x);
//	if (!*coord)
//	{
//		free_2d_arr((void **) values);
//		return (1);
//	}
//	map->max_x--;
//	map->colors[y] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
//	if (!map->colors[y])
//	{
//		free_2d_arr((void **) values);
//		return (1);
//	}
//	if (read_colors(values, map->colors[y], map->max_x) != 0)
//		error_check = 1;
//	free_2d_arr((void **) values);
//	return (error_check);
//}
//
//static int	panic_free(int **coord, char ***colors, int y)
//{
//	int	i;
//	int	x;
//
//	i = y;
//	if (coord)
//	{
//		while (coord[i])
//		{
//			free(coord[i]);
//			coord[i++] = NULL;
//		}
//	}
//	i = y;
//	if (colors)
//	{
//		while (colors[i])
//		{
//			x = -1;
//			while (colors[i][++x])
//				free(colors[i][x]);
//			free(colors[i]);
//			colors[i++] = NULL;
//		}
//	}
//	return (1);
//}
//
//int	read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data)
//{
//	int			err_check;
//	char		*const next_line = get_and_trim_next_line(map_fd, " \n\t\f\r");
//
//	err_check = 0;
//	if (next_line != NULL && y < MAX_MAP_SIZE)// && ((ft_isdigit(next_line[0])
//		err_check = read_map(map, map_fd, y + 1, exit_data);
//		//|| next_line[0] == '-' || next_line[0] == '+')))
//	else
//	{
//		if (next_line)
//			free(next_line);
//		if (y == 0 || y >= MAX_MAP_SIZE || err_check != 0)
//		{
//			return (1);
//		}
//		map->coord = (int **) ft_calloc((y + 1), sizeof(int *));
//		map->colors = (char ***) ft_calloc((y + 1), sizeof(char **));
//		if (!map->coord || !map->colors)
//		{
//			return (1);
//		}
//		map->max_y = y - 1;
//		//ft_printf("FUCKING WYYYY\n");
//		return (0);
//	}
//	if (err_check != 1)
//		err_check = get_x_z(map, &map->coord[y], next_line, y);
//	if (err_check != 0)
//		err_check = panic_free(map->coord, map->colors, y + 1);
//	return (free(next_line), err_check);
//}
