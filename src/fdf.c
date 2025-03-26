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

mlx_image_t	*img_test(mlx_t	*mlx)
{
	mlx_image_t	*test_img;

	test_img = mlx_new_image(mlx, 256, 256);
	if (!test_img)
		return (NULL);
	int	x = 30;
	int	y = 30;
	while (y <= 100)
	{
		while (x <= 100)
		{
			mlx_put_pixel(test_img, x, y, 0xF008080F);
			x++;
		}
		x = 30;
		y++;
	}
	return (test_img);
}

int	main(int argc, char *argv[])
{
	t_map	map;
	mlx_t	*main_window;
	mlx_image_t	*test_img;

	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	map = parse_map(argv[1]);
	//test_recursive_print_map(map.coord, map.max_y, map.max_x);
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	main_window = mlx_init(2048, 1536, argv[1], false);
	if (!main_window)
	{
		free_2d_arr((void **) map.coord);
		error_close(main_window);
		exit (EXIT_FAILURE);
	}
	test_img = img_test(main_window);
	if (!test_img)
	{
		error_close(main_window);
		exit (EXIT_FAILURE);
	}
	mlx_image_to_window(main_window, test_img, 0, 0);
	mlx_loop(main_window);
	mlx_terminate(main_window);
	free_2d_arr((void **) map.coord);
	exit(EXIT_SUCCESS);
}
