/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_drawing.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/30 20:20:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/11 19:50:33 by avaliull     ########   odam.nl          */
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
	uint8_t	red;
	uint8_t	green;
	uint8_t	blue;
	uint8_t	opacity;

	//printf("start color: %d\n", start->color.rgba);
	//printf("end color: %d\n", end->color.rgba);
	//printf("end color r: %d\n", end->color.r);
	//printf("start color r: %d\n", start->color.r);
	//printf("end color g: %d\n", end->color.g);
	//printf("start color g: %d\n", start->color.g);
	//printf("end color b: %d\n", end->color.b);
	//printf("start color b: %d\n", start->color.b);
	//printf("end color a: %d\n", end->color.a);
	//printf("start color a: %d\n", start->color.a);
	red = start->color.r + ((end->color.r - start->color.r) / distance) * i;
	green = start->color.g + ((end->color.g - start->color.g) / distance) * i;
	blue = start->color.b + ((end->color.b - start->color.b) / distance) * i;
	opacity = start->color.a + ((end->color.a - start->color.a) / distance) * i;
	//ft_printf("red: %d\n", red);
	//ft_printf("green: %d\n", green);
	//ft_printf("blue: %d\n", blue);
	//ft_printf("alpha: %d\n", opacity);
	return ((red << 24) + (green << 16) + (blue << 8) + opacity);
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
		mlx_put_pixel(fdf->img, start.x + i, start.y, get_color(&start, &end, distance_x, i));
		if (decision_parameter >= 0)
		{
			start.y += direction;
			decision_parameter -= 2 * distance_x;
		}
		decision_parameter += 2 * distance_y;
	}
}

void	draw_line(t_fdf *fdf, t_pixel start, t_pixel end)
{
	// ADD COORDINATE ERROR CHECKING
	//ft_printf("start.x: %d, end.x: %d, start.y: %d, end.y: %d\n", start.x, end.x, start.y, end.y);
	if (abs(end.x - start.x) > abs(end.y - start.y))
		horizontal(fdf, start, end);
	else
		vertical(fdf, start, end);
}

