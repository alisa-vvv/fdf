/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_drawing.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/30 20:20:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/10 21:02:18 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>

static void	swap_dots(t_dot *start, t_dot *end, t_colors *colors)
{
	int		tmp_dot;
	char	*tmp_color;

	tmp_dot = start->x;
	start->x = end->x;
	end->x = tmp_dot;
	tmp_dot = start->y;
	start->y = end->y;
	end->y = tmp_dot;
	tmp_color = colors->start;
	colors->start = colors->end;
	colors->end = tmp_color;
}

static t_grading	get_grading(t_colors colors, int distance)
{
	t_grading	grading;
	int			end_color;
	int			start_color;
	const int	start_color_len = ft_strlen(colors.start + 2);
	const int	end_color_len = ft_strlen(colors.end + 2);

	//ft_printf("colors: %s, %s\n", colors.start, colors.end);
	start_color = hexstr_to_int(colors.start + 2);
	end_color = hexstr_to_int(colors.end + 2);
	//ft_printf("colors int: %d, %d\n", start_color, end_color);
	//ft_printf("distance: %d\n", distance);
	grading.red = (start_color >> 24) & 0xFF;
	grading.red_increment = ((end_color >> 24) & 0xFF - grading.red) / distance;
	//ft_printf("red: %d\n", grading.red);
	//ft_printf("red end: %d\n", ((end_color >> 24) & 0xFF);
	//ft_printf("red inc: %d\n", grading.red_increment);
	grading.green = (start_color >> 16) & 0xFF;
	grading.green_increment = ((end_color >> 16) & 0xFF - grading.green) / distance;
	//ft_printf("green: %d\n", grading.green);
	//ft_printf("green end: %d\n", ((end_color >> 16) & 0xFF));
	//ft_printf("green inc: %d\n", grading.green_increment);
	grading.blue = (start_color >> 8) & 0xFF;
	grading.blue_increment = ((end_color >> 8) & 0xFF - grading.blue) / distance;
	//ft_printf("blue: %d\n", grading.blue);
	//ft_printf("blue end: %d\n", channel_end);
	//ft_printf("blue inc: %d\n", grading.blue_increment);
	if (start_color_len == 8)
		grading.opacity = start_color & 0xFF;
	else
		grading.opacity = 0xFF;
	if (end_color_len == 8)
		grading.opacity_increment = (end_color & 0xFF - grading.opacity) / distance;
	else
		grading.opacity_increment = (0xFF - grading.opacity) / distance;
	//ft_printf("opacity: %d\n", grading.opacity);
	//ft_printf("opacity end: %d\n", end_color & 0xFF);
	//ft_printf("opacity inc: %d\n", grading.opacity_increment);
	return (grading);
}

static	uint32_t	get_next_color(t_grading *grading, int i)
{
	int			rounded_red;
	int			rounded_green;
	int			rounded_blue;
	int			rounded_opacity;
	uint32_t	color;

	grading->red += grading->red_increment * i;
	grading->green += grading->green_increment * i;
	grading->blue += grading->blue_increment * i;
	grading->opacity += grading->opacity_increment * i;

	ft_printf("grading red: %d\n", grading->red);
	ft_printf("grading green: %d\n", grading->red);
	ft_printf("grading blue: %d\n", grading->red);
	ft_printf("grading opacity: %d\n", grading->red);
	rounded_red = grading->red << 24;
	rounded_green = grading->green << 16;
	rounded_blue = grading->blue << 8;
	rounded_opacity = grading->opacity;
	color = rounded_red | rounded_green | rounded_blue | rounded_opacity;
	return (color);
}

static void	put_rgb_pixel(t_fdf *fdf, int x_pos, int y_pos, uint32_t color)
{
	//printf("int color: %u\n", (unsigned) color);
	mlx_put_pixel(fdf->img, x_pos, y_pos, color);
}

static void	vertical(t_fdf *fdf, t_dot start, t_dot end, t_colors colors)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	int	i;
	t_grading	grading;

	if (start.y > end.y)
		swap_dots(&start, &end, &colors);
	direction = 1;
	if (end.x - start.x < 0)
		direction = -direction;
	distance_x = (end.x - start.x) * direction;
	distance_y = (end.y - start.y);
	decision_parameter = 2 * distance_x - distance_y;
	i = -1;
	grading = get_grading(colors, distance_y);
	while (++i < distance_y)
	{
		put_rgb_pixel(fdf, start.x, start.y + i, get_next_color(&grading, i));
		if (decision_parameter >= 0)
		{
			start.x += direction;
			decision_parameter -= 2 * distance_y;
		}
		decision_parameter += 2 * distance_x;
	}
}

//replace start and end with fdf_vecs so I can actually have color isndie
static void	horizontal(t_fdf *fdf, t_dot start, t_dot end, t_colors colors)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	t_grading	grading;
	int	i;

	if (start.x > end.x)
		swap_dots(&start, &end, &colors);
	direction = 1;
	if (end.y - start.y < 0)
		direction = -direction;
	distance_x = (end.x - start.x);
	distance_y = (end.y - start.y) * direction;
	decision_parameter = 2 * distance_y - distance_x;
	grading = get_grading(colors, distance_x);
	i = -1;
	while (++i < distance_x)
	{
		//this should be replaced with a wrapper that calculates color of pixel
		put_rgb_pixel(fdf, start.x + i, start.y, get_next_color(&grading, i));
		if (decision_parameter >= 0)
		{
			start.y += direction;
			decision_parameter -= 2 * distance_x;
		}
		decision_parameter += 2 * distance_y;
	}
}

// 1. convert each channel value to int separately (r, g, b, a)
// 2.1 end_r - start_r = diff_r
// 2.2-4 repeat for each of the channels
// 3.1 diff_r / distance = increment
// 3.2-4 repeat for each of the channels
// 4. save this in a struct (fucking great, love my structs (no)
// 5. for each pixel, peform:
// 	1) channel_value = start.channel + increment * i
// 	2) get_rgba on all channels
// 6. the result is my color
void	draw_line(t_fdf *fdf, t_dot start, t_dot end, t_colors colors)
{
	// ADD COORDINATE ERROR CHECKING
	//ft_printf("start.x: %d, end.x: %d, start.y: %d, end.y: %d\n", start.x, end.x, start.y, end.y);
	if (abs(end.x - start.x) > abs(end.y - start.y))
		horizontal(fdf, start, end, colors);
	else
		vertical(fdf, start, end, colors);
}

