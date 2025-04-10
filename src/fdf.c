/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/10 18:01:14 by avaliull     ########   odam.nl          */
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

void	draw_connected_dots(t_fdf *fdf, int range_len,
						 t_four_vector vec, t_four_vector next_vec)
{
	const int	width_offset = (fdf->img->width - range_len) / 2;
	const int	height_offset = (fdf->img->height - range_len) / 2;
	//(void) range_len;
	//const int	width_offset = 0;
	//const int	height_offset = 0;
	t_dot		start_dot;
	t_dot		end_dot;

	start_dot.x = vec.x + width_offset;
	start_dot.y = vec.y + height_offset;
	end_dot.x = next_vec.x + width_offset;
	end_dot.y = next_vec.y + height_offset;
	draw_line(fdf, start_dot, end_dot, 0x008080FF);
}

void	adjust_coordinates_for_step(t_four_vector *vector, const int step)
{
	vector->x *= step;
	vector->y *= step;
	vector->z = vector->z * step / 8;
}

//void	isometric_projection(t_four_vector *vec, t_four_vector *next_vec_x,
//						t_four_vector *next_vec_y)
//{
//	vec->z = -vec->z;
//	next_vec_x->z = -next_vec_x->z;
//	next_vec_y->z = -next_vec_y->z;
//	rotate_along_x(vec, -45);
//	rotate_along_x(next_vec_x, -45);
//	rotate_along_x(next_vec_y, -45);
//	rotate_along_y(vec, 35.3644);
//	rotate_along_y(next_vec_x, 35.3644);
//	rotate_along_y(next_vec_y, 35.3644);
//}

void	isometric_projection(t_four_vector *vec, t_four_vector *next_vec_x,
						t_four_vector *next_vec_y)
{
	vec->z = -vec->z;
	next_vec_x->z = -next_vec_x->z;
	next_vec_y->z = -next_vec_y->z;
	rotate_along_x(vec, -45);
	rotate_along_x(next_vec_x, -45);
	rotate_along_x(next_vec_y, -45);
	rotate_along_y(vec, 35.3644);
	rotate_along_y(next_vec_x, 35.3644);
	rotate_along_y(next_vec_y, 35.3644);
	rotate_along_z(vec, 30);
	rotate_along_z(next_vec_x, 30);
	rotate_along_z(next_vec_y, 30);
}

void	isometric_rotate_right(t_four_vector *vec, t_four_vector *next_vec_x,
						t_four_vector *next_vec_y)
{
	rotate_along_z(vec, 90);
	rotate_along_z(next_vec_x, 90);
	rotate_along_z(next_vec_y, 90);
}

void	isometric_rotate_left(t_four_vector *vec, t_four_vector *next_vec_x,
						t_four_vector *next_vec_y)
{
	rotate_along_z(vec, -90);
	rotate_along_z(next_vec_x, -90);
	rotate_along_z(next_vec_y, -90);
}

void	put_aligned_image_to_window(t_fdf *fdf, const int range_len)
{
	const int	width_offset = (fdf->img->width - range_len) / 4;
	const int	height_offset = (fdf->img->height - range_len) / 2;
	mlx_image_to_window(fdf->window, fdf->img, -width_offset, -height_offset);
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
			adjust_coordinates_for_step(&vec, step);
			if (x < fdf->map.max_x)
			{
				allocate_four_vector(&next_vec_x,
						 x + 1, y, fdf->map.coord[y][x + 1]);
				adjust_coordinates_for_step(&next_vec_x, step);
			}
			if (y < fdf->map.max_y)
			{
				allocate_four_vector(&next_vec_y,
						 x, y + 1, fdf->map.coord[y + 1][x]);
				adjust_coordinates_for_step(&next_vec_y, step);
			}
			map_to_range(&vec, centered_range, old_range);
			map_to_range(&next_vec_x, centered_range, old_range);
			map_to_range(&next_vec_y, centered_range, old_range);
			//isometric_rotate_right(&vec, &next_vec_x, &next_vec_y);
			//isometric_rotate_left(&vec, &next_vec_x, &next_vec_y);
			isometric_projection(&vec, &next_vec_x, &next_vec_y);
			map_to_range(&vec, old_range, centered_range);
			map_to_range(&next_vec_x, old_range, centered_range);
			map_to_range(&next_vec_y, old_range, centered_range);
			if (x < fdf->map.max_x)
				draw_connected_dots(fdf, centered_range[1] - centered_range[0],
						vec, next_vec_x);
			if (y < fdf->map.max_y)
				draw_connected_dots(fdf, centered_range[1] - centered_range[0],
					vec, next_vec_y);
			x++;
		}
		y++;
	}
	put_aligned_image_to_window(fdf, centered_range[1] - centered_range[0]);
}

void	create_map_image(t_fdf *fdf, const int step, int old_range[2])
{
	const int	image_size_iterator = 512;
	const int	range_len = (old_range[1] - old_range[0]);
	int			image_size;
	int			height_diff;
	int			width_diff;

	ft_printf("range_len: %d\n", range_len);
	ft_printf("range_len / step: %d\n", range_len / step);
	image_size = 2048;
	while (image_size < range_len * 2 + step * 2)
		image_size += image_size_iterator;
	height_diff = (fdf->window->height - image_size);
	width_diff = (fdf->window->width - image_size);
	ft_printf("image_size: %d\n, height_diff: %d\n, width_diff: %d\n", image_size, height_diff, width_diff);
	fdf->img = mlx_new_image(fdf->window, image_size, image_size);
	if (!fdf->img)
	{
		fdf->img = NULL;
		return ;
	}
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
}

void	create_window(t_fdf *fdf, char *map_file)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	if (!fdf->window)
		clean_exit(fdf);
}

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
	test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	create_map_image(fdf, step, old_range);
	test_draw_2d_map(fdf, step, centered_range, old_range);
	mlx_loop(fdf->window);
	clean_exit(fdf);
}
