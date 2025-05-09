/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_creation.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 15:54:52 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 16:32:13 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

void	put_aligned_image_to_window(t_fdf *fdf)
{
	int	width_offset;
	int	height_offset;
	width_offset = (int) (fdf->window->width - fdf->img->width) / 2;
	height_offset = (int) (fdf->window->height - fdf->img->height) / 2;
	mlx_image_to_window(fdf->window, fdf->img, width_offset, height_offset);
}

void	draw_segment(t_fdf *fdf, t_transformed_map *map,
				  t_fdf_vec vec, t_fdf_vec next_vec)
{

	int			width_offset;
	int			height_offset;
	t_dot		start_dot;
	t_dot		end_dot;
	t_colors	colors;

	width_offset = (fdf->img->width - map->max_x - map->min_x) / 2;
	height_offset = (fdf->img->height - map->max_y - map->min_y) / 2;
	start_dot.x = vec.x + width_offset;
	start_dot.y = vec.y + height_offset;
	end_dot.x = next_vec.x + width_offset;
	end_dot.y = next_vec.y + height_offset;
	colors.start = vec.color;
	colors.end = next_vec.color;
	draw_line(fdf, start_dot, end_dot, colors);
}

void	create_map_image(t_fdf *fdf, t_transformed_map *transformed_map)
{
	int	image_width;
	int	image_height;
	int	map_height;
	int	map_width;

	image_width = 2048;
	image_height = 2048;
	map_width = (int) (transformed_map->max_x - transformed_map->min_x);
	map_width = abs(map_width);
	map_height = (int) (transformed_map->max_y - transformed_map->min_y);
	map_height = abs(map_height);
	if (image_width < map_width + fdf->zoom * 4)
		image_width = map_width + fdf->zoom * 4;
	if (image_height < map_height + fdf->zoom * 4)
		image_height = map_height + fdf->zoom * 4;
	fdf->img = mlx_new_image(fdf->window, image_width, image_height);
	if (!fdf->img)
	{
		fdf->img = NULL;
		// ADD ERROR MANAGEMENT
		return ;
	}
}

void	draw_map(t_fdf *fdf, t_transformed_map *map)
{
	int					x;
	int					y;

	create_map_image(fdf, map);
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			if (x < fdf->map.max_x)
			{
				draw_segment(fdf, map, map->coord[y][x], map->coord[y][x + 1]);
			}
			if (y < fdf->map.max_y)
				draw_segment(fdf, map, map->coord[y][x], map->coord[y + 1][x]);
			x++;
		}
		y++;
	}
}

