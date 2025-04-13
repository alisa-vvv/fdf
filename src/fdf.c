/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/13 20:40:51 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>
#include "MLX42/MLX42.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

/*	The magic numbers for centering were arrived at through
 *	guesswork/approximation
*/
void	draw_segment(t_fdf *fdf, t_transformed_map *map,
				  t_four_vector vec, t_four_vector next_vec)
{
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);

//	const int	width_offset = (int) fdf->map.max_x * 50 * 1.13;
//	const int	height_offset = (int) fdf->map.max_y * 50 * 2.05;
	int	width_offset;
	int	height_offset;
	t_dot		start_dot;
	t_dot		end_dot;

	width_offset = (fdf->img->width - map->max_x - map->min_x) / 2;
	height_offset = (fdf->img->height - map->max_y - map->min_y) / 2;
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

void	isometric_transform(t_four_vector *vec)
{
	vec->z = -vec->z;
	rotate_along_x(vec, -45);
	rotate_along_y(vec, 35.3644);
	rotate_along_z(vec, 30);
}

void	put_aligned_image_to_window(t_fdf *fdf)
{
	int	width_offset;
	int	height_offset;
	width_offset = (int) (fdf->window->width - fdf->img->width) / 2;
	height_offset = (int) (fdf->window->height - fdf->img->height) / 2;
	ft_printf("windowheight: %d\n", fdf->window->height);
	ft_printf("image height: %d\n", fdf->img->height);
	ft_printf("width_offset: %d\n", width_offset);
	ft_printf("height_offset: %d\n", height_offset);
	mlx_image_to_window(fdf->window, fdf->img, width_offset, height_offset);
}

//void	center_vector_xy(t_map *map, t_four_vector *vec, const int step)
//{
//	vec->x -= map->max_x / 2 * step;
//	vec->y -= map->max_y / 2 * step;
//}

t_four_vector		*allocate_vector_array(int size)
{
	t_four_vector	*new_array;

	new_array = ft_calloc(size, sizeof(t_four_vector));
	ft_printf("checking size x: %d\n", size);
	if (!new_array)
	{
		ft_printf("something is wonky\n");
		// ADD ERROR_MANAGEMENT!!
	}
	return (new_array);
}

t_transformed_map	*alloc_transofrmed_map(t_fdf *fdf)
{
	t_transformed_map	*new_map;
	t_four_vector		**new_vector_array;
	int					y;

	new_vector_array = ft_calloc(fdf->map.max_y + 1, sizeof(*new_vector_array));
	if (!new_vector_array)
	{
		// ADD ERROR MANAGEMENT
		return (NULL);
	}
	new_map = ft_calloc(1, sizeof(t_transformed_map));
	if (!new_map)
	{
		free(new_vector_array);
		return (NULL);
		// ADD ERROR MANAGEMENT
	}
	new_map->coord = new_vector_array;
	y = -1;
	while (++y <= fdf->map.max_y)
	{
		new_vector_array[y] = allocate_vector_array(fdf->map.max_x + 1);
		if (!new_vector_array[y])
		{
			ft_printf("something is wonky\n");
			// ADDD ERROR MANAGEMENT!
		}
	}
	return (new_map);
}

void	create_map_image(t_fdf *fdf, t_transformed_map *transformed_map)
{
	int	image_width;
	int	image_height;
	int	map_height;
	int	map_width;

	image_width = 2048;
	image_height = 2048;
	map_width = (int) (transformed_map->max_x - transformed_map->min_x);
	map_width = abs(map_width);
	map_height = (int) (transformed_map->max_y - transformed_map->min_y);
	map_height = abs(map_height);
	if (image_width < map_width + fdf->step * 4)
		image_width = map_width + fdf->step * 4;
	if (image_height < map_height + fdf->step * 4)
		image_height = map_height + fdf->step * 4;
	fdf->img = mlx_new_image(fdf->window, image_width, image_height);
	if (!fdf->img)
	{
		fdf->img = NULL;
		// ADD ERROR MANAGEMENT
		return ;
	}
}

void	add_vector_to_map(t_fdf *fdf, int x, int y, t_transformed_map *new_map)
{
	t_four_vector	*vec;

	vec = &new_map->coord[y][x];
	allocate_four_vector(vec, x, y, fdf->map.coord[y][x]);
	adjust_coordinates_for_step(vec, fdf->step);
}

void	rotate_and_project(t_transformed_map *map,
						t_four_vector *vec, int *rotation_count)
{
	int	local_rotation_count;

	if (*rotation_count == 3)
		rotate_along_z(vec, -90);
	else if (*rotation_count)
	{
		local_rotation_count = *rotation_count;
		while (local_rotation_count--)
			rotate_along_z(vec, 90);
	}
	isometric_transform(vec);
	if (vec->x < map->min_x)
		map->min_x = vec->x;
	if (vec->x > map->max_x)
		map->max_x = vec->x;
	if (vec->y < map->min_y)
		map->min_y = vec->y;
	if (vec->y > map->max_y)
		map->max_y = vec->y;
}

t_transformed_map	*transform_map(t_fdf *fdf, int *rotation_count)
{
	int					x;
	int					y;
	t_transformed_map	*transformed_map;

	
	transformed_map = alloc_transofrmed_map(fdf);
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			add_vector_to_map(fdf, x, y, transformed_map);
			rotate_and_project(transformed_map, &transformed_map->coord[y][x],
					  rotation_count);
			if (x < fdf->map.max_x)
				add_vector_to_map(fdf, x + 1, y, transformed_map);
			if (y < fdf->map.max_y)
				add_vector_to_map(fdf, x, y + 1, transformed_map);
			x++;
		}
		y++;
	}
	return (transformed_map);
}

void	draw_map(t_fdf *fdf, t_transformed_map *map)
{
	int					x;
	int					y;

	create_map_image(fdf, map);
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
			if (x < fdf->map.max_x)
				draw_segment(fdf, map, map->coord[y][x], map->coord[y][x + 1]);
			if (y < fdf->map.max_y)
				draw_segment(fdf, map, map->coord[y][x], map->coord[y + 1][x]);
			x++;
		}
		y++;
	}
}

void	main_drawing_loop(t_fdf *fdf)
{
	int					rotation_count;
	t_transformed_map	*map;

	rotation_count = 0;
	map = transform_map(fdf, &rotation_count);
	draw_map(fdf, map);
	put_aligned_image_to_window(fdf);
}

void	create_window(t_fdf *fdf, char *map_file)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
	if (!fdf->window)
		clean_exit(fdf);
}

int	main(int argc, char *argv[])
{
	t_fdf		*fdf;
	const int	step = 50;

	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		clean_exit(fdf);
	fdf->map = parse_map(argv[1]);
	fdf->step = step;
	test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	//create_map_image(fdf, step, old_range);
	main_drawing_loop(fdf);
	mlx_loop(fdf->window);
	clean_exit(fdf);
}
