/* ************************************************************************** */
/*                                                                            */
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

#ifndef	SQUARE_SIZE
# define SQUARE_SIZE 70
#endif

void	move_square(t_fdf *fdf, e_action action)
{
	const int	step = 1;
	int	i;
	i = 1;
	if (action == up)
	{
		while (i++ <= step)
			fdf->img->instances[0].y -= 1;
	}
	else if (action == down)
		fdf->img->instances[0].y += 10;
	else if (action == left)
		fdf->img->instances[0].x -= 10;
	else if (action == right)
		fdf->img->instances[0].x += 10;
}

void	img_test(t_fdf *fdf)
{
	int	x = 30;
	int	y = 30;

	fdf->img = mlx_new_image(fdf->window, 256, 256);
	if (!fdf->img)
	{
		fdf->img = NULL;
		return ;
	}
		while (y <= 100)
		{
			while (x <= 100)
			{
				mlx_put_pixel(fdf->img, x, y, 0x008080FF);
				x++;
			}
			x = 30;
			y++;
		}
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
	//test_recursive_print_map(map.coord, map.max_y, map.max_x);
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, argv[1], false);
	mlx_key_hook(fdf->window, &fdf_key_hook, fdf);
	if (!fdf->window)
		clean_exit(fdf);
	img_test(fdf);
	if (!fdf->img)
		clean_exit(fdf);
	fdf->x_zero = 0;
	fdf->y_zero = 0;
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
	mlx_loop(fdf->window);
	clean_exit(fdf);
}
