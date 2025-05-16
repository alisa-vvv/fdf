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

// here, should add a variablke called char **color_map
// then using ft_split we can see if there's a color variable in the cell
// then save it to color map
// color map can then be either merged with the regular map or exist on it's won
// it's the same size and has the same indexes as the regular map so I can iterate through it whenever I iterate through the map
// I don't remember if any of the functions I have can convert from hex string to int, but it shouldn't be hard to make.
// then those values can be added to vectors and used for color grading the image
// profit

// just parse values here to get colors???? what was I doiung befoire/??
// also jsut pass map
void		read_colors(char **values, char **colors, int max_x)
{
	int		x;
	char	**color_check;

	x = -1;
	while (++x <= max_x)
	{
		color_check = ft_split(values[x], ',');
		if (!color_check)
		{
			// ADD ERROR MANAGEMENT
		}
		if (color_check[1] == NULL)
		{
			colors[x] = ft_strdup(COLOR_WHITE);
			if (!colors[x])
			{
				/// ADD ERROR MANAGEMTN
			}
		}
		else
			colors[x] = color_check[1];
		free(color_check[0]);
		free(color_check);
	}
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
	//just split again with comma. if colors[1] is empty, set default color. else,
	//get the actual color
	max_x = 0;
	*coord = allocate_x(*coord, values, 0, &max_x);
	colors[y] = (char **) ft_calloc(max_x + 2, sizeof(char *));
	read_colors(values, colors[y], max_x);
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
		map->colors = (char ***) ft_calloc((y + 1), sizeof(char **));
		map->max_y = y - 1;
		return ;
	}
	// pass colors here, make sure it's initialized
	map->max_x = get_x_z(&map->coord[y], map->colors, next_line, y);
	if (map->coord == NULL || map->colors == NULL)
		error_exit(exit_data, MALLOC_ERR, false);
	free(next_line);
}

t_map	parse_map(t_exit_data *exit_data)
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
	//ft_printf("coord\n");
	//int	y = -1;
	//while (++y <= map.max_y)
	//{
	//	ft_printf("%d: ", y);
	//	int	x = -1;
	//	while (++x <= map.max_x)
	//		ft_printf("%d:%d, ", x, map.coord[y][x]);
	//	ft_printf("\n");
	//}
	get_max_min_z(map.coord, max_min_z, map.max_x, map.max_y);
	//ft_printf("color map\n");
	//int	y = -1;
	//while (++y <= map.max_y)
	//{
	//	ft_printf("%d: ", y);
	//	int	x = -1;
	//	while (++x <= map.max_x)
	//		ft_printf("%d:%s, ", x, map.colors[y][x]);
	//	ft_printf("\n");
	//}
	map.min_z = max_min_z[0];
	map.max_z = max_min_z[1];
	close(exit_data->map_fd);
	exit_data->map_fd = -1;
	return (map);
}

