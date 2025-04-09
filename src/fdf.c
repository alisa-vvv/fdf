/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/09 17:30:01 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
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

#define START_OFFSET 1000

int	get_new_max(t_map *map, int *max_point, int *min_point, const int step)
{
	int	maximum_distance;

	if (*max_point < map->max_x * step)
		*max_point = map->max_x * step;
	if (*max_point < map->max_y * step)
		*max_point = map->max_y * step;
	if (*min_point > 0)
		*min_point = 0;
	maximum_distance = *max_point - *min_point + 1;
	return (maximum_distance);
}

void	test_draw_2d_map(t_fdf *fdf, const int step,
					  int centered_range[2], int old_range[2])
{
	int				x;
	int				y;
	t_four_vector 	vec;
	t_four_vector 	next_vec_x;
	t_four_vector 	next_vec_y;

	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			allocate_four_vector(&vec, x, y, fdf->map.coord[y][x]);
			test_print_four_vector(&vec, "vec");
			if (x < fdf->map.max_x)
			{
				allocate_four_vector(&next_vec_x,
						 x + 1, y, fdf->map.coord[y][x + 1]);
				test_print_four_vector(&next_vec_x, "next_vec_x");
			}
			if (y < fdf->map.max_y)
			{
				allocate_four_vector(&next_vec_y,
						 x, y + 1, fdf->map.coord[y + 1][x]);
				test_print_four_vector(&next_vec_y, "next_vec_y");
			}

			(void) step;
			map_to_range(&vec, centered_range, old_range);
			map_to_range(&next_vec_x, centered_range, old_range);
			map_to_range(&next_vec_y, centered_range, old_range);

			rotate_along_x(&vec, 45);
			rotate_along_x(&next_vec_x, 45);
			rotate_along_x(&next_vec_y, 45);
			rotate_along_y(&vec, -45);
			rotate_along_y(&next_vec_x, -45);
			rotate_along_y(&next_vec_y, -45);

			if (x < fdf->map.max_x)
				draw_line(fdf,
			  (t_dot) {(int) vec.x + START_OFFSET, (int) vec.y + START_OFFSET},
			  (t_dot) {(int) next_vec_x.x + START_OFFSET, (int) next_vec_x.y + START_OFFSET}, 0x008080FF);
			if (y < fdf->map.max_y)
				draw_line(fdf,
			  (t_dot) {(int) vec.x + START_OFFSET, (int) vec.y + START_OFFSET},
			  (t_dot) {(int) next_vec_y.x + START_OFFSET, (int) next_vec_y.y + START_OFFSET}, 0x008080FF);
			x++;
		}
		y++;
	}
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
}

void	create_window(t_fdf *fdf, char *map_file,
				   int centered_range[2], int old_range[2])
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	if (!fdf->window)
		clean_exit(fdf);
	fdf->img = mlx_new_image(fdf->window, 2048, 2048);
	if (!fdf->img)
	{
		fdf->img = NULL;
		return ;
	}
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
	test_draw_2d_map(fdf, 100, centered_range, old_range);
	mlx_image_to_window(fdf->window, fdf->img, 0, 0);
	mlx_loop(fdf->window);
}

void	calculate_map_ranges(t_map *map, const int step,
						  int *centered_range, int *old_range)
{
	int	min_point;
	int	max_point;
	int	new_max_distance;

	min_point = map->min_z * step;
	max_point = map->max_z * step;
	new_max_distance = get_new_max(map, &max_point, &min_point, step);
	old_range[0] = min_point;
	old_range[1] = max_point;
	centered_range[0] = -new_max_distance / 2;
	centered_range[1] = new_max_distance / 2;
}

int	main(int argc, char *argv[])
{
	t_fdf		*fdf;
	int			old_range[2];
	int			centered_range[2];
	const int	step = 50;

	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		clean_exit(fdf);
	fdf->map = parse_map(argv[1]);
	calculate_map_ranges(&fdf->map, step, centered_range, old_range);
	//test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1], centered_range, old_range);
	clean_exit(fdf);
}
