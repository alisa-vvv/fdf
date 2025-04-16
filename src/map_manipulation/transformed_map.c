/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   transformed_map.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 16:28:02 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 16:28:51 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_four_vector		*allocate_vector_array(int size)
{
	t_four_vector	*new_array;

	new_array = ft_calloc(size, sizeof(t_four_vector));
	if (!new_array)
		return (NULL);
	return (new_array);
}

t_transformed_map	*alloc_transofrmed_map(t_fdf *fdf, t_exit_data *exit_data)
{
	t_transformed_map	*new_map;
	t_four_vector		**new_vector_array;
	int					y;

	new_map = ft_calloc(1, sizeof(t_transformed_map));
	if (!new_map)
		error_exit(exit_data, MALLOC_ERR, false);
	new_vector_array = ft_calloc(fdf->map.max_y + 2, sizeof(*new_vector_array));
	if (!new_vector_array)
		error_exit(exit_data, MALLOC_ERR, false);
	new_map->coord = new_vector_array;
	y = -1;
	while (++y <= fdf->map.max_y)
	{
		new_vector_array[y] = allocate_vector_array(fdf->map.max_x + 2);
		if (!new_vector_array[y])
			error_exit(exit_data, MALLOC_ERR, false);
	}
	return (new_map);
}

void	add_vector_to_map(t_fdf *fdf, int x, int y, t_transformed_map *new_map)
{
	t_four_vector	*vec;

	vec = &new_map->coord[y][x];
	allocate_four_vector(vec, x, y, fdf->map.coord[y][x]);
}

t_transformed_map	*transform_map(t_fdf *fdf, int *rotation_count, t_exit_data *exit_data)
{
	int					x;
	int					y;
	t_transformed_map	*transformed_map;

	
	transformed_map = alloc_transofrmed_map(fdf, exit_data);
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			add_vector_to_map(fdf, x, y, transformed_map);
			rotate_and_project(transformed_map, fdf,
					  &transformed_map->coord[y][x], rotation_count);
			if (x < fdf->map.max_x)
				add_vector_to_map(fdf, x + 1, y, transformed_map);
			if (y < fdf->map.max_y)
				add_vector_to_map(fdf, x, y + 1, transformed_map);
			x++;
		}
		y++;
	}
	return (transformed_map);
}
