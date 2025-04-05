/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/02 20:24:15 by avaliull     ########   odam.nl          */
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

t_dot	transform_vector(int x, int y, int width, int height)
{
	t_dot		new_dot;
	int			new_x[2];
	int			new_y[2];

	//new_x[0] = x * width * 0.5;
	//new_x[1] = y * -width * 0.5;
	//new_y[0] = x * height * 0.25;
	//new_y[1] = y * height * 0.25;
	new_x[0] = x * width * 0.5;
	new_x[1] = -y * width * 0.5;
	new_y[0] = x * 0.5 * height * 0.5;
	new_y[1] = y * 0.5 * height * 0.5;
	new_dot.x = new_x[0] + new_x[1] + OFFSET_2;
	new_dot.y = new_y[0] + new_y[1] + OFFSET_2;
	ft_printf("new_dot.x: %d\n", new_dot.x);
	ft_printf("new_dot.y: %d\n", new_dot.y);
	return (new_dot);
}

#define START_OFFSET 150

// Formula for mapping ranges:
// X is for current range values, X' for desired
// X' = X'min + (X'max - X'min) / (Xmax - Xmin) * X - Xmin

void	map_to_range(t_map *map, t_four_vector *vector,
				  int new_range[2], int old_range[2])
{
	//const int	max_z = 9; // THIS NEEDS TO BE REMOVED.
	(void) map;
	const float	new_range_len = new_range[1] - new_range[0];
	const float	old_range_len = old_range[1] - old_range[0];
	float		new_x;
	float		new_y;
	float		new_z;

	printf("old x: %d\n", (int) vector->x);
	printf("x - old_range[0]: %f\n", vector->x - old_range[0]);
	printf("old y: %d\n", (int) vector->y);
	printf("old z: %d\n", (int) vector->z);
	printf("new_range_len: %f\n", new_range_len);
	printf("old_range_len: %f\n", old_range_len);
	printf("new_range[0]: %d\n", new_range[0]);
	new_x = new_range[0] + new_range_len / old_range_len * (vector->x - old_range[0]);
	new_y = new_range[0] + new_range_len / old_range_len * (vector->y - old_range[0]);
	new_z = new_range[0] + new_range_len / old_range_len * (vector->z - old_range[0]);
	vector->x = new_x;
	vector->y = new_y;
	vector->z = new_z;
	vector->i = 1;
 	printf("new x: %f\n", vector->x);
 	printf("new y: %f\n", vector->y);
 	printf("new z: %f\n", vector->z);
}

float	map_point_to_range(int point, int new_range[2], int old_range[2])
{
	const float	new_range_len = new_range[1] - new_range[0];
	const float	old_range_len = old_range[1] - old_range[0];

	return (new_range[0] + new_range_len / old_range_len * (point - old_range[0]));
}

void	orthogonal_projection_matrix(t_four_vector *vector, t_map *map,
								  const int step)
{
	t_four_vector	new_vector;
	float			min_val;
	float			max_val;

	min_val = -1;
	max_val = map_point_to_range(map->max_x * step, (int[2]) {-1, 1}, (int[2]) {0, map->max_x * step});
	printf("max_val x: %f\n", max_val);
	printf("max_val y: %f\n", max_val);
	new_vector.x = vector->x * 2 / (max_val - min_val);
	max_val = map_point_to_range(map->max_y * step, (int[2]) {-1, 1}, (int[2]) {0, map->max_y * step});
	new_vector.y = vector->y * 2 / (max_val - min_val);
	printf("max_val y: %f\n", max_val);
	max_val = map_point_to_range(9 * step, (int[2]) {-1, 1}, (int[2]) {0, 9 * step});
	printf("max_val z: %f\n", max_val);
	new_vector.z = vector->z * -2 / (max_val - min_val);
	new_vector.z = 1;
	vector->x = new_vector.x;
	vector->y = new_vector.y;
	vector->z = new_vector.z;
}

void	three_rotations_isometric(t_four_vector *vector)
{
	t_four_vector	new_vector;
	float			dot_product;
	
	dot_product = vector->x;
}

void	try_simple_isometric(t_four_vector *vector)
{
	//const int		step = 100;
	t_four_vector	new_vector;
	float const		scalar = 1 / sqrt(6);
	float			dot_product;

//	dot_product = vector->x * scalar * sqrt(3);
//	dot_product += vector->y * scalar;
//	dot_product += vector->z * scalar * sqrt(2);
//	new_vector.x = dot_product;
//	dot_product = vector->y * scalar * 2;
//	dot_product += vector->z * scalar * -sqrt(2);
//	new_vector.y = dot_product;
//	dot_product = vector->x * scalar * -sqrt(3);
//	dot_product += vector->y * scalar;
//	dot_product += vector->z * scalar * sqrt(2);
//	new_vector.z = dot_product;
	dot_product = sqrt(3) * vector->x;
	dot_product += -sqrt(3) * vector->z;
	new_vector.x = dot_product * scalar;
	dot_product = vector->x;
	dot_product += 2 * vector->y;
	dot_product += vector->z;
	new_vector.y = dot_product * scalar;
	dot_product = sqrt(2) * vector->x;
	dot_product += -sqrt(2) * vector->y;
	dot_product += sqrt(2) * vector->z;
	new_vector.z = dot_product * scalar;
	vector->x = new_vector.x;
	vector->y = new_vector.y;
	vector->z = new_vector.z;
}

void	allocate_four_vector(t_four_vector *vector, int x, int y, int z)
{
	const int	step = 100;
	const int	height_step = -sqrt(step);

	vector->x = x * step;
	vector->y = y * step;
	vector->z = z * height_step;
	vector->i = 1;
}

void	print_four_vector(t_four_vector *vector, char *vec_name)
{
	printf("\n");
	printf("vector: %s\n", vec_name);
	printf("x: %f\n", vector->x);
	printf("y: %f\n", vector->y);
	printf("z: %f\n", vector->z);
	printf("\n\n");
}

void	test_draw_2d_map(t_fdf *fdf, const int step)
{
	int				x;
	int				y;
	//int				z;
	t_four_vector 	vec;
	t_four_vector 	next_vec_x;
	t_four_vector 	next_vec_y;

	(void) step;
	y = 0;
	while (y <= fdf->map.max_y)
	{
		x = 0;
		while (x <= fdf->map.max_x)
		{
		//	z = step;
			ft_printf("checking inital x: %d\n", x);
			ft_printf("checking inital y: %d\n", y);
			ft_printf("checking inital z: %d\n", fdf->map.coord[y][x]);
			allocate_four_vector(&vec, x, y, fdf->map.coord[y][x]);
			print_four_vector(&vec, "vec");
			if (x < fdf->map.max_x)
			{
				allocate_four_vector(&next_vec_x, x + 1, y, fdf->map.coord[y][x + 1]);
				print_four_vector(&next_vec_x, "next_vec_x");
			}
			if (y < fdf->map.max_y)
			{
				allocate_four_vector(&next_vec_y, x, y + 1, fdf->map.coord[y + 1][x]);
				print_four_vector(&next_vec_y, "next_vec_y");
			}
		//	map_to_range(&fdf->map, &vec, (int[2]) {-1, 1}, (int[2]) {0, 2048});
		//	map_to_range(&fdf->map, &next_vec_x, (int[2]) {-1, 1}, (int[2]) {0, 2048});
		//	map_to_range(&fdf->map, &next_vec_y, (int[2]) {-1, 1}, (int[2]) {0, 2048});
			try_simple_isometric(&vec);
			try_simple_isometric(&next_vec_x);
			try_simple_isometric(&next_vec_y);
		//	map_to_range(&fdf->map, &vec, (int[2]) {0, 2048}, (int[2]) {-1, 1});
		//	map_to_range(&fdf->map, &next_vec_x, (int[2]) {0, 2048}, (int[2]) {-1, 1});
		//	map_to_range(&fdf->map, &next_vec_y, (int[2]) {0, 2048}, (int[2]) {-1, 1});
		//	orthogonal_projection_matrix(&vec, &fdf->map, step);
		//	orthogonal_projection_matrix(&next_vec_x, &fdf->map, step);
		//	orthogonal_projection_matrix(&next_vec_y, &fdf->map, step);
			if (x < fdf->map.max_x)
				draw_line(fdf,
			  (t_dot) {(int) vec.x + START_OFFSET, (int) vec.y},
			  (t_dot) {(int) next_vec_x.x + START_OFFSET, (int) next_vec_x.y}, 0x008080FF);
//				draw_line(fdf,
//			  transform_vector((int) vec.x * step + START_OFFSET,
//					  (int) vec.y * step, step, step),
//			  transform_vector((int) (vec.x + 1) * step + START_OFFSET,
//					  (int) vec.y * step, step, step),
//			  0x008080FF);

			if (y < fdf->map.max_y)
				draw_line(fdf,
			  (t_dot) {(int) vec.x + START_OFFSET, (int) vec.y},
			  (t_dot) {(int) next_vec_y.x + START_OFFSET, (int) next_vec_y.y}, 0x008080FF);
			//	draw_line(fdf,
			//  transform_vector((int) vec.x * step + START_OFFSET,
			//		  (int) vec.y * step, step, step),
			//  transform_vector((int) vec.x * step + START_OFFSET,
			//		  (int) (vec.y + 1) * step, step, step),
			//  0x008080FF);
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
	fdf->img = mlx_new_image(fdf->window, 2048, 2048);
	if (!fdf->img)
	{
		fdf->img = NULL;
		return ;
	}
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
	test_draw_2d_map(fdf, 100);
	//draw_line(fdf, (t_dot) {309, 30}, (t_dot) {3, 18}, 0x008080FF);
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
	test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	clean_exit(fdf);
}
