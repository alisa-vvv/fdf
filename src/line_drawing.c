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

static void	put_rgb_pixel(t_fdf *fdf, int x_pos, int y_pos, uint32_t color)
{
	//printf("int color: %u\n", (unsigned) color);
	mlx_put_pixel(fdf->img, x_pos, y_pos, color);
}

static uint32_t	get_next_color(int distance, int i, t_colors colors)
{
	uint32_t	next_color;
	uint32_t	start;
	uint32_t	end;

	//ft_printf("color not recorded?: %s\n", colors.start);
	//if ((*(colors.start + 2)) != 0)
	//{
	//	//ft_printf("x_pos: %d, y_pos: %d\n", x_pos, y_pos);
	//	//ft_printf("colorstring: %s\n", colors.start);
	//}
	start = hexstr_to_uint32(colors.start + 2);
	end = hexstr_to_uint32(colors.end + 2);
	next_color = (end - start) / distance * i;
	return (next_color);
}

static void	vertical(t_fdf *fdf, t_dot start, t_dot end, t_colors colors)
{
	int	direction;
	int	distance_y;
	int	distance_x;
	int	decision_parameter;
	int	i;

	if (start.y > end.y)
		swap_dots(&start, &end, &colors);
	direction = 1;
	if (end.x - start.x < 0)
		direction = -direction;
	distance_x = (end.x - start.x) * direction;
	distance_y = (end.y - start.y);
	decision_parameter = 2 * distance_x - distance_y;
	i = -1;
	while (++i < distance_y)
	{
		put_rgb_pixel(fdf, start.x, start.y + i, get_next_color(distance_y, i, colors));
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
	int	i;

	if (start.x > end.x)
		swap_dots(&start, &end, &colors);
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
		put_rgb_pixel(fdf, start.x + i, start.y, get_next_color(distance_x, i, colors));
		if (decision_parameter >= 0)
		{
			start.y += direction;
			decision_parameter -= 2 * distance_x;
		}
		decision_parameter += 2 * distance_y;
	}
}

void	draw_line(t_fdf *fdf, t_dot start, t_dot end, t_colors colors)
{
	// ADD COORDINATE ERROR CHECKING
	//ft_printf("start.x: %d, end.x: %d, start.y: %d, end.y: %d\n", start.x, end.x, start.y, end.y);
	if (abs(end.x - start.x) > abs(end.y - start.y))
		horizontal(fdf, start, end, colors);
	else
		vertical(fdf, start, end, colors);
}

