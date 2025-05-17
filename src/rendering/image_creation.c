/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_creation.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 15:54:52 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/17 18:44:18 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_aligned_image_to_window(t_fdf *fdf, t_exit_data *exit_data)
{
	int	width_offset;
	int	height_offset;

	width_offset = (int) (fdf->window->width - fdf->img->width) / 2;
	height_offset = (int) (fdf->window->height - fdf->img->height) / 2;
	mlx_image_to_window(fdf->window, fdf->img, width_offset, height_offset);
	if (!fdf->img || !fdf->window)
		error_exit(exit_data, MLX42_ERR, true);
	fdf->img->instances[0].x += fdf->param.x_offset * fdf->param.zoom;
	fdf->img->instances[0].y += fdf->param.y_offset * fdf->param.zoom;
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
	if (image_width < map_width + fdf->param.zoom * 4)
		image_width = map_width + fdf->param.zoom * 4;
	if (image_height < map_height + fdf->param.zoom * 4)
		image_height = map_height + fdf->param.zoom * 4;
	if (fdf->img)
		mlx_delete_image(fdf->window, fdf->img);
	fdf->img = mlx_new_image(fdf->window, image_width, image_height);
}

void	draw_map(t_fdf *fdf, t_exit_data *exit_data, t_transformed_map *map)
{
	int	x;
	int	y;

	if (fdf->img)
		mlx_delete_image(fdf->window, fdf->img);
	create_map_image(fdf, map);
	if (!fdf->img)
		error_exit(exit_data, MLX42_ERR, true);
	y = 0;
	while (y <= fdf->map->max_y)
	{
		x = 0;
		while (x <= fdf->map->max_x)
		{
			if (x < fdf->map->max_x)
				create_line(fdf, map, map->coord[y][x], map->coord[y][x + 1]);
			if (y < fdf->map->max_y)
				create_line(fdf, map, map->coord[y][x], map->coord[y + 1][x]);
			x++;
		}
		y++;
	}
}

