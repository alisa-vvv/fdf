/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_drawing.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/30 20:20:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/17 18:56:30 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"

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

void	create_line(t_fdf *fdf, t_transformed_map *map,
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
