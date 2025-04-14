/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 17:22:25 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "MLX42/MLX42.h"
#include "ft_printf.h"

/*	Error messages	*/
# define MALLOC_ERR "Error! malloc()"
# define DUP2_ERR "Error! dup2()"
# define FORK_ERR "Error! fork()"
# define PIPE_ERR "Error! pipe()"
# define FD_ERR "Error! Invalid file descriptor"
# define CLOSE_ERR "Error! close()"

typedef struct	s_dot
{
	int	x;
	int	y;
}	t_dot;

typedef struct	s_four_vector
{
	float	x;
	float	y;
	float	z;
	float	w;
}	t_four_vector;

typedef enum	e_direction
{
	up,
	down,
	left,
	right,
}	e_direction;

typedef	struct	s_map
{
	int	**coord;
	int	max_x;
	int	max_y;
	int	max_z;
	int	min_z;
}	t_map;

typedef struct	s_transformed_map
{
	t_four_vector	**coord;
	float	min_x;
	float	max_x;
	float	min_y;
	float	max_y;
}	t_transformed_map;

typedef struct	s_fdf
{
	t_map	map;
	int		zoom;
	mlx_t	*window;
	mlx_image_t	*img;
}	t_fdf;

/*	Main functions	*/
void	clean_exit(t_fdf *fdf, int map_fd);
t_map	parse_map(const int map_fd);

/*	Vector/matrix rotations, transformations, projection	*/
void	rotate_along_x(t_four_vector *vector, float angle);
void	rotate_along_y(t_four_vector *vector, float angle);
void	rotate_along_z(t_four_vector *vector, float angle);
void	rotate_and_project(t_transformed_map *map, t_fdf *fdf,
						t_four_vector *vec, int *rotation_count);

/*	Matrix and vector allocation/math	*/
void	vector_by_scalar(t_four_vector *vector, const float scalar);
void	allocate_four_vector(t_four_vector *vector, int x, int y, int z);

/*	Map transformation	*/
t_transformed_map	*transform_map(t_fdf *fdf, int *rotation_count);

/*	Line drawing	*/
void	draw_line(t_fdf *fdf, t_dot start, t_dot end, int color);

/*	Image creation	*/
void	draw_map(t_fdf *fdf, t_transformed_map *map);
void	put_aligned_image_to_window(t_fdf *fdf);

/*	Utils	*/
void	free_2d_arr(void **arr);

/*	TEST (COMMENT THEM OUT)	*/
void	test_print_map(int **coord, int max_x, int max_y);
void	test_fdf_key_hook(mlx_key_data_t keydata, void *param);
void	test_print_four_vector(t_four_vector *vector, char *vec_name);
//void	test_move_square(t_fdf *fdf, e_action action);

#endif
