/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   line_drawing.c                                    :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/30 20:20:12 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/30 20:21:19 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

static void	swap_t_dots(t_dot *start, t_dot *end)
{
	int	tmp_swap;

	tmp_swap = start->x;
	start->x = end->x;
	end->x = tmp_swap;
	tmp_swap = start->y;
	start->y = end->y;
	end->y = tmp_swap;
}

static void	vertical(t_fdf *fdf, t_dot start, t_dot end, int color)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	int	i;

	if (start.y > end.y)
		swap_t_dots(&start, &end);
	direction = 1;
	if (end.x - start.x < 0)
		direction = -direction;
	distance_x = (end.x - start.x) * direction;
	distance_y = (end.y - start.y);
	decision_parameter = 2 * distance_x - distance_y;
	i = -1;
	while (++i < distance_y)
	{
		mlx_put_pixel(fdf->img, start.x, start.y + i, color);
		if (decision_parameter >= 0)
		{
			start.x += direction;
			decision_parameter -= 2 * distance_y;
		}
		decision_parameter += 2 * distance_x;
	}
}

static void	horizontal(t_fdf *fdf, t_dot start, t_dot end, int color)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	int	i;

	if (start.x > end.x)
		swap_t_dots(&start, &end);
	direction = 1;
	if (end.y - start.y < 0)
		direction = -direction;
	distance_x = (end.x - start.x);
	distance_y = (end.y - start.y) * direction;
	decision_parameter = 2 * distance_y - distance_x;
	i = -1;
	while (++i < distance_x)
	{
		mlx_put_pixel(fdf->img, start.x + i, start.y, color);
		if (decision_parameter >= 0)
		{
			start.y += direction;
			decision_parameter -= 2 * distance_x;
		}
		decision_parameter += 2 * distance_y;
	}
}

void	draw_line(t_fdf *fdf, t_dot start, t_dot end, int color)
{
	// ADD COORDINATE ERROR CHECKING
	if (abs(end.x - start.x) > abs(end.y - start.y))
		horizontal(fdf, start, end, color);
	else
		vertical(fdf, start, end, color);
}

