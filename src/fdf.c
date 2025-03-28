/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/28 16:49:32 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/28 17:11:23 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

/* ************************************************************************** */ /*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/21 14:51:43 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// question: use struct for each individual coordinate point? feels wrong.
// alternative: use a single 3d array. then points can be found by coordinates.
// question: what is x=0? what is y=0? is it the top of the map?
// probably, feels the easiest since it's the order in which string is read.
// left to right, up to down
//

void	draw_line(t_fdf *fdf, t_dot start, t_dot end, int color)
{
	const int	dx = end.x - start.x;
	const int	dy = end.y - start.y;
	int	p;
	int	x;
	int	y;

	x = start.x;
	y = start.y;
	p = 2 * dy - dx;
	while (x < end.x || y < end.y)
	{
		if (p >= 0)
		{
			mlx_put_pixel(fdf->img, x, y, color);
			y++;
			p = p + 2 * dy - 2 * dx;
		}
		else
		{
			mlx_put_pixel(fdf->img, x, y, color);
			p = p + 2 * dy;
			x++;
		}
	}
}

void	test_draw_2d_map(t_fdf *fdf, const int step)
{
	int	x;
	int	y;
	int	z;

	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			z = 0;
			while (z < fdf->map.coord[y][x] * 2)
			{
				draw_line(fdf, (t_dot) {x * step, (y * step) + z},
			  (t_dot) { (x * step) + fdf->map.coord[y][x] * 2, (y * step) + z},
			  0xFF0000FF);
				z++;
			}
			if (x < fdf->map.max_x)
				draw_line(fdf, (t_dot) {x * step, y * step},
			  (t_dot) {(x + 1) * step, (y * step)}, 0x008080FF);
			if (y < fdf->map.max_y)
				draw_line(fdf, (t_dot) {x * step, y * step},
			  (t_dot) {x * step, (y + 1) * step}, 0x008080FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
}

void	create_window(t_fdf *fdf, char *map_file)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	if (!fdf->window)
		clean_exit(fdf);
	fdf->img = mlx_new_image(fdf->window, 2048, 1536);
	if (!fdf->img)
	{
		fdf->img = NULL;
		return ;
	}
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
	test_draw_2d_map(fdf, 50);
	mlx_loop(fdf->window);
}

int	main(int argc, char *argv[])
{
	t_fdf	*fdf;

	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		clean_exit(fdf);
	fdf->map = parse_map(argv[1]);
	test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	clean_exit(fdf);
}
