/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_drawing.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/30 20:20:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/11 17:34:34 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <math.h>
#include <stdio.h>

static void	swap_pixels(t_pixel *start, t_pixel *end)
{
	t_pixel		tmp_pixel;

	tmp_pixel = *start;
	*start = *end;
	*end = tmp_pixel;
}

static	uint32_t	get_color(t_pixel *start, t_pixel *end, int distance, int i)
{
	int			red;
	int			green;
	int			blue;
	int			opacity;

	red = start->red + ((end->red - start->red) / distance * i);
	green = start->green + ((end->green - start->green) / distance * i);
	blue = start->blue + ((end->blue - start->blue) / distance * i);
	opacity = start->opacity + ((end->opacity - start->opacity) / distance * i);
	return (red << 24 | green << 16 | blue << 8 | opacity);
}

static void	vertical(t_fdf *fdf, t_pixel start, t_pixel end)
{
	int			direction;
	int			distance_y;
	int			distance_x;
	int			decision_parameter;
	uint32_t	color;
	int			i;

	if (start.y > end.y)
		swap_pixels(&start, &end);
	direction = 1;
	if (end.x - start.x < 0)
		direction = -direction;
	distance_x = (end.x - start.x) * direction;
	distance_y = (end.y - start.y);
	decision_parameter = 2 * distance_x - distance_y;
	i = -1;
	while (++i < distance_y)
	{
		color = get_color(&start, &end, distance_y, i);
		mlx_put_pixel(fdf->img, start.x, start.y + i, color);
		if (decision_parameter >= 0)
		{
			start.x += direction;
			decision_parameter -= 2 * distance_y;
		}
		decision_parameter += 2 * distance_x;
	}
}

//replace start and end with fdf_vecs so I can actually have color isndie
static void	horizontal(t_fdf *fdf, t_pixel start, t_pixel end)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	int	i;

	if (start.x > end.x)
		swap_pixels(&start, &end);
	direction = 1;
	if (end.y - start.y < 0)
		direction = -direction;
	distance_x = (end.x - start.x);
	distance_y = (end.y - start.y) * direction;
	decision_parameter = 2 * distance_y - distance_x;
	i = -1;
	while (++i < distance_x)
	{
		//this should be replaced with a wrapper that calculates color of pixel
		mlx_put_pixel(fdf->img, start.x + i, start.y, get_color(&start, &end, distance_x, i));
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
void	draw_line(t_fdf *fdf, t_pixel start, t_pixel end)
{
	// ADD COORDINATE ERROR CHECKING
	//ft_printf("start.x: %d, end.x: %d, start.y: %d, end.y: %d\n", start.x, end.x, start.y, end.y);
	if (abs(end.x - start.x) > abs(end.y - start.y))
		horizontal(fdf, start, end);
	else
		vertical(fdf, start, end);
}

