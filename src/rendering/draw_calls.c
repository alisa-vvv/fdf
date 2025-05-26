/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   draw_calls.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/20 20:38:09 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/25 21:39:12 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	redraw(t_fdf *fdf, t_exit_data *exit_data, t_transformed_map *map)
{
	transform_map(fdf, map);
	draw_map(fdf, exit_data, map);
	put_aligned_image_to_window(fdf, exit_data);
}

void	initial_draw(t_fdf *fdf, t_exit_data *exit_data, t_transformed_map *map)
{
	transform_map(fdf, map);
	while (map->max_x > MAX_IMAGE_SIZE || map->max_y > MAX_IMAGE_SIZE
		|| map->min_x < MIN_IMAGE_SIZE || map->min_y < MIN_IMAGE_SIZE)
	{
		fdf->param.zoom -= 5;
		if (fdf->param.zoom <= 0)
			error_exit(exit_data, BIG_MAP_ERR, false);
		transform_map(fdf, map);
	}
	fdf->param.zoom_max = fdf->param.zoom;
	while ((map->max_y - map->min_y + fdf->param.zoom > WINDOW_HEIGHT
			|| map->max_x - map->min_x + fdf->param.zoom > WINDOW_WIDTH)
		&& fdf->param.zoom > 1)
	{
		fdf->param.zoom -= 1;
		if (fdf->param.zoom <= 0)
			fdf->param.zoom = 1;
		transform_map(fdf, map);
	}
	fdf->param.zoom_default = fdf->param.zoom;
	draw_map(fdf, exit_data, map);
	put_aligned_image_to_window(fdf, exit_data);
}
