/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coordinate_adjustments.c                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 16:22:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 16:23:45 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	adjust_coordinates_for_zoom(t_four_vector *vector, const int zoom)
{
	int	height_factor;

	height_factor = 2;
	vector->x *= zoom;
	vector->y *= zoom;
	vector->z = vector->z * zoom / height_factor;
}

void	isometric_transform(t_four_vector *vec)
{
	vec->z = -vec->z;
	rotate_along_x(vec, -45);
	rotate_along_y(vec, 35.3644);
	rotate_along_z(vec, 30);
}

void	rotate_and_project(t_transformed_map *map, t_fdf *fdf,
						t_four_vector *vec, int *rotation_count)
{
	int	local_rotation_count;

	if (*rotation_count == 3)
		rotate_along_z(vec, -90);
	else if (*rotation_count)
	{
		local_rotation_count = *rotation_count;
		while (local_rotation_count--)
			rotate_along_z(vec, 90);
	}
	isometric_transform(vec);
	adjust_coordinates_for_zoom(vec, fdf->zoom);
	if (vec->x < map->min_x)
		map->min_x = vec->x;
	if (vec->x > map->max_x)
		map->max_x = vec->x;
	if (vec->y < map->min_y)
		map->min_y = vec->y;
	if (vec->y > map->max_y)
		map->max_y = vec->y;
}

