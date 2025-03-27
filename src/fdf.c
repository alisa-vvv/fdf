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

void	draw_red_line(t_fdf *fdf, int cur_pixel[2], int end_x)
{
	while (cur_pixel[0] <= end_x)
	{
		mlx_put_pixel(fdf->img, cur_pixel[0], cur_pixel[1], 0xFF0000FF);
		cur_pixel[0]++;
	}
}
void	draw_horizontal_line(t_fdf *fdf, int cur_pixel[2], int end_x)
{
	while (cur_pixel[0] <= end_x)
	{
		mlx_put_pixel(fdf->img, cur_pixel[0], cur_pixel[1], 0x008080FF);
		cur_pixel[0]++;
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
		ft_printf("y? %d\n", y);
		x = 0;
		while (x <= fdf->map.max_x)
		{
			z = 0;
			while (z <= fdf->map.coord[y][x] * 2)
			{
				draw_red_line(fdf, (int[2]) {x * step, (y * step) + z}, (x * step) + fdf->map.coord[y][x] * 2);
				z++;
			}
			if (x < fdf->map.max_x)
				draw_horizontal_line(fdf, (int[2]) {x * step, y * step}, (x + 1) * step);
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
