/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   transformed_map.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/15 15:33:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/22 20:30:11 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

t_fdf_vec	*allocate_vector_array(int size)
{
	t_fdf_vec	*new_array;

	new_array = ft_calloc(size, sizeof(t_fdf_vec));
	if (!new_array)
		return (NULL);
	return (new_array);
}

void	alloc_transformed_map(t_fdf *fdf, t_exit_data *exit_data)
{
	t_fdf_vec			**vectors;
	t_transformed_map	*new_map;
	int					y;

	new_map = ft_calloc(1, sizeof(t_transformed_map));
	exit_data->transformed_map = new_map;
	if (!new_map)
		error_exit(exit_data, MALLOC_ERR, false);
	vectors = ft_calloc(fdf->map->max_y + 2, sizeof(*vectors));
	if (!vectors)
		error_exit(exit_data, MALLOC_ERR, false);
	new_map->coord = vectors;
	y = -1;
	while (++y <= fdf->map->max_y)
	{
		vectors[y] = allocate_vector_array(fdf->map->max_x + 2);
		if (!vectors[y])
			error_exit(exit_data, MALLOC_ERR, false);
	}
}

void	add_vector_to_map(t_fdf *fdf, int x, int y, t_transformed_map *new_map)
{
	t_fdf_vec *const	vec = &new_map->coord[y][x];
	const int			z = fdf->map->coord[y][x];

	vec->x = x;
	vec->y = y;
	vec->z = z;
	if (fdf->param.color_mode == from_map)
		vec->color = fdf->map->colors[y][x];
	else if (fdf->param.color_mode == height_gradient)
	{
		vec->color = fdf->map->height_colors[y][x];
	}
}

void	clear_transformed_map(t_fdf *fdf, t_transformed_map *map,
						int max_x, int max_y)
{
	int	y;

	y = 0;
	while (y <= max_y)
		ft_bzero(map->coord[y++], max_x);
	add_vector_to_map(fdf, 0, 0, map);
	project_map(map, fdf, &map->coord[0][0]);
	map->min_x = map->coord[0][0].x;
	map->max_x = map->coord[0][0].x;
	map->min_y = map->coord[0][0].y;
	map->max_y = map->coord[0][0].y;
}

void	transform_map(t_fdf *fdf, t_transformed_map *transformed_map)
{
	int	x;
	int	y;

	y = 0;
	clear_transformed_map(fdf, transformed_map,
		fdf->map->max_x, fdf->map->max_y);
	while (y <= fdf->map->max_y)
	{
		x = 0;
		while (x <= fdf->map->max_x)
		{
			add_vector_to_map(fdf, x, y, transformed_map);
			project_map(transformed_map, fdf, &transformed_map->coord[y][x]);
			if (x < fdf->map->max_x)
				add_vector_to_map(fdf, x + 1, y, transformed_map);
			if (y < fdf->map->max_y)
				add_vector_to_map(fdf, x, y + 1, transformed_map);
			x++;
		}
		y++;
	}
}
