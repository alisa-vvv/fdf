/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_algo.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/17 18:39:22 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/22 19:27:44 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"

static uint32_t	get_color(t_pixel *start, t_pixel *end, int distance, int i)
{
	int	red;
	int	green;
	int	blue;
	int	opacity;
	//ft_printf("start->color.r: %d\n", start->color.r);
	red = start->color.r + ((end->color.r - start->color.r) * i / distance);
	//ft_printf("red? %d\n", red);
	green = start->color.g + ((end->color.g - start->color.g) * i / distance);
	//ft_printf("green? %d\n", green);
	blue = start->color.b + ((end->color.b - start->color.b) * i / distance);
	//ft_printf("blue? %d\n", blue);
	opacity = start->color.a + ((end->color.a - start->color.a) * i / distance);
	//ft_printf("opacity? %d\n", opacity);
	return ((red << 24) + (green << 16) + (blue << 8) + opacity);
}

static void	vertical(t_fdf *fdf, t_pixel start, t_pixel end)
{
	int			direction;
	int			distance_y;
	int			distance_x;
	int			decision_parameter;
	int			i;

	direction = 1;
	if (end.x - start.x < 0)
		direction = -direction;
	distance_x = (end.x - start.x) * direction;
	distance_y = (end.y - start.y);
	decision_parameter = 2 * distance_x - distance_y;
	i = -1;
	while (++i < distance_y)
	{
		mlx_put_pixel(fdf->img, start.x, start.y + i,
			get_color(&start, &end, distance_y, i));
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

	direction = 1;
	if (end.y - start.y < 0)
		direction = -direction;
	distance_x = (end.x - start.x);
	distance_y = (end.y - start.y) * direction;
	decision_parameter = 2 * distance_y - distance_x;
	i = -1;
	while (++i < distance_x)
	{
		mlx_put_pixel(fdf->img, start.x + i, start.y,
			get_color(&start, &end, distance_x, i));
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
	if (abs(end.x - start.x) > abs(end.y - start.y))
	{
		if (start.x < end.x)
			horizontal(fdf, start, end);
		else
			horizontal(fdf, end, start);
	}
	else
	{
		if (start.y < end.y)
			vertical(fdf, start, end);
		else
			vertical(fdf, end, start);
	}
}
