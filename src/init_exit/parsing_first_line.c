/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   parsing_first_line.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/25 20:21:34 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/25 20:25:18 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

char	**read_first_line(t_map *map, int map_fd, t_exit_data *exit_data)
{
	char	*first_line;
	char	*cleaned_line;
	char	**split_line;

	first_line = get_next_line(map_fd);
	if (!first_line)
		error_exit(exit_data, PARSE_ERR, false);
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

void	add_first_line(char **line, t_map *map, t_exit_data *exit_data)
{
	int	x;
	int	error_check;

	map->coord[0] = (int *) ft_calloc(map->max_x + 1, sizeof(int));
	if (!map->coord[0])
	{
		free_2d_arr((void **) line);
		error_exit(exit_data, MALLOC_ERR, false);
	}
	map->colors[0] = (char **) ft_calloc(map->max_x + 2, sizeof(char *));
	if (!map->colors[0])
	{
		free_2d_arr((void **) line);
		error_exit(exit_data, MALLOC_ERR, false);
	}
	x = 0;
	while (x <= map->max_x)
	{
		map->coord[0][x] = ft_atoi(line[x]);
		error_check = read_colors(line, map->colors[0], x);
		x++;
	}
	free_2d_arr((void **) line);
	if (error_check != 0)
		error_exit(exit_data, MALLOC_ERR, false);
}

