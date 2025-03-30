/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/28 19:54:23 by avaliull     ########   odam.nl          */
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

#define OFFSET_2 10

t_dot	transform_vector(int x, int y, int width, int height)
{
	t_dot		new_dot;
	int			new_x[2];
	int			new_y[2];

	height ++;
	//new_x[0] = x * width * 0.5;
	//new_x[1] = y * -width * 0.5;
	//new_y[0] = x * height * 0.25;
	//new_y[1] = y * height * 0.25;
	new_x[0] = x * width * 0.5;
	new_x[1] = -y * width * 0.5;
	new_y[0] = x * 0.5 * height * 0.5;
	new_y[1] = y * 0.5 * height * 0.5;
	new_dot.x = new_x[0] + new_x[1];
	new_dot.y = new_y[0] + new_y[1];
	return (new_dot);
}

void	create_vector(int **coord, int y, int x, int *vec)
{
	vec[0] = x;
	vec[1] = y;
	vec[2] = coord[y][x];
	vec[3] = 1;
}

#define START_OFFSET 100

//void	test_draw_2d_map(t_fdf *fdf, const int step)
//{
//	int	x;
//	int	y;
//	int	z;
//	//int	vec[4];
//
//	y = 0;
//	while (y <= fdf->map.max_y)
//	{
//		x = 0;
//		while (x <= fdf->map.max_x)
//		{
//		//	z = 0;
//		//	while (z < fdf->map.coord[y][x] * 2)
//		//	{
//		//		draw_line(fdf, (t_dot) {x * step, (y * step) + z},
//		//	  (t_dot) { (x * step) + fdf->map.coord[y][x] * 2, (y * step) + z},
//		//	  0xFF0000FF);
//		//		z++;
//		//	}
//			//create_vector(fdf->map.coord, y, x, vec);
//			
//			//z = fdf->map.coord[y][x];
//			z = step; 
//			if (x < fdf->map.max_x)
//				draw_line(fdf,
//			  transform_vector(x * step + START_OFFSET,
//					  y * step, step, z),
//			  transform_vector((x + 1) * step + START_OFFSET,
//					  y * step, step, z),
//			  0x008080FF);
//			//	draw_line(fdf, (t_dot) {x * step, y * step},
//			//  (t_dot) {(x + 1) * step, (y * step)}, 0x008080FF);
//			if (y < fdf->map.max_y)
//				draw_line(fdf,
//			  transform_vector(x * step + START_OFFSET,
//					  y * step, step, z),
//			  transform_vector(x * step + START_OFFSET,
//					  (y + 1) * step, step, z),
//			  0x008080FF);
//			//	draw_line(fdf, (t_dot) {x * step, y * step},
//			//  (t_dot) {x * step, (y + 1) * step}, 0x008080FF);
//			x++;
//		}
//		y++;
//	}
//	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
//}

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
	//test_draw_2d_map(fdf, 12);
	draw_line(fdf, (t_dot) {30, 30}, (t_dot) {20, 25}, 0x008080FF);
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
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
	///test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	clean_exit(fdf);
}
