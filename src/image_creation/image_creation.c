/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   image_creation.c                                  :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/14 15:54:52 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/13 18:40:34 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	put_aligned_image_to_window(t_fdf *fdf)
{
	int	width_offset;
	int	height_offset;

	width_offset = (int) (fdf->window->width - fdf->img->width) / 2;
	height_offset = (int) (fdf->window->height - fdf->img->height) / 2;
	mlx_image_to_window(fdf->window, fdf->img, width_offset, height_offset);
	fdf->img->instances[0].x += fdf->param.x_offset * fdf->param.zoom;
	fdf->img->instances[0].y += fdf->param.y_offset * fdf->param.zoom;
}

void	get_rgba_from_str(t_pixel *pixel, char *color_str)
{
	int	i;
	int	code_len;

	i = -1;
	while (color_str[++i])
	{
		if (ft_isspace(color_str[i]))
			color_str[i] = '\0';
	}
	code_len = ft_strlen(color_str + 2);
	pixel->color.rgba = 0;
	pixel->color.rgba = hexstr_to_int(color_str + 2, code_len);
	if (code_len < 7)
		pixel->color.rgba = (pixel->color.rgba << 8) + 0xFF;
}

void	alt_color(t_pixel *start_pixel, t_pixel *end_pixel,
				  e_map_color color_mode)
{
	if (color_mode == default_color)
	{
		start_pixel->color.rgba = RGBA_TEAL;
		end_pixel->color.rgba = RGBA_TEAL;
	}
	else if (color_mode == no_color)
	{
		start_pixel->color.rgba = RGBA_WHITE;
		end_pixel->color.rgba = RGBA_WHITE;
	}
}

void	draw_segment(t_fdf *fdf, t_transformed_map *map,
				  t_fdf_vec vec, t_fdf_vec next_vec)
{

	int			width_offset;
	int			height_offset;
	t_pixel		start_pixel;
	t_pixel		end_pixel;

	width_offset = (fdf->img->width - map->max_x - map->min_x) / 2;
	height_offset = (fdf->img->height - map->max_y - map->min_y) / 2;
	start_pixel.x = vec.x + width_offset;
	start_pixel.y = vec.y + height_offset;
	end_pixel.x = next_vec.x + width_offset;
	end_pixel.y = next_vec.y + height_offset;
	if (fdf->param.color_mode == from_map)
	{
		get_rgba_from_str(&start_pixel, vec.color);
		get_rgba_from_str(&end_pixel, next_vec.color);
	}
	else
		alt_color(&start_pixel, &end_pixel, fdf->param.color_mode);
	draw_line(fdf, start_pixel, end_pixel);
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
	if (!fdf->img)
	{
		fdf->img = NULL;
		// ADD ERROR MANAGEMENT
		return ;
	}
}

void	draw_map(t_fdf *fdf, t_transformed_map *map)
{
	int	x;
	int	y;

	if (fdf->img)
		mlx_delete_image(fdf->window, fdf->img);
	create_map_image(fdf, map);
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			if (x < fdf->map.max_x)
				draw_segment(fdf, map, map->coord[y][x], map->coord[y][x + 1]);
			if (y < fdf->map.max_y)
				draw_segment(fdf, map, map->coord[y][x], map->coord[y + 1][x]);
			x++;
		}
		y++;
	}
}

