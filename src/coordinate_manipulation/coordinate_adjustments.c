/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   coordinate_adjustments.c                          :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 16:22:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/20 20:45:47 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	zoom(t_fdf_vec *vector, int zoom)
{
	if (zoom < 1)
		zoom = 1;
	vector->x *= zoom;
	vector->y *= zoom;
	vector->z = vector->z * zoom / HEIGHT_DEFAULT;
}

void	isometric_transform(t_fdf_vec *vec)
{
	vec->z = -vec->z;
	rotate_along_x(vec, -45);
	rotate_along_y(vec, 35.3644);
	rotate_along_z(vec, 30);
}

void	project_map(t_transformed_map *map, t_fdf *fdf, t_fdf_vec *vec)
{
	rotate_along_z(vec, 90 * fdf->param.rotation_count);
	zoom(vec, fdf->param.zoom);
	isometric_transform(vec);
	if (vec->x < map->min_x)
		map->min_x = vec->x;
	if (vec->x > map->max_x)
		map->max_x = vec->x;
	if (vec->y < map->min_y)
		map->min_y = vec->y;
	if (vec->y > map->max_y)
		map->max_y = vec->y;
}
