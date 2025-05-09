/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/16 20:39:38 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "MLX42/MLX42.h"
#include "ft_printf.h"

/*	Error messages	*/
# define PARSE_ERR "Error! Parsing fail"
# define MALLOC_ERR "Error! malloc()"
# define DUP2_ERR "Error! dup2()"
# define FD_ERR "Error! Invalid file descriptor"
# define MLX42_ERR "Error! MLX42"

/*	Default values	*/
# define DEFAULT_COLOR "0x008080FF"

typedef struct	s_dot
{
	int	x;
	int	y;
}	t_dot;

typedef struct	s_grading
{
	int	red;
	int	green;
	int	blue;
	int	opacity;
	int	red_increment;
	int	green_increment;
	int	blue_increment;
	int	opacity_increment;
}	t_grading;

typedef struct	s_colors
{
	char	*start;
	char	*end;
}	t_colors;

typedef struct	s_fdf_vec
{
	float	x;
	float	y;
	float	z;
	char	*color;
}	t_fdf_vec;

typedef enum	e_direction
{
	up,
	down,
	left,
	right,
}	e_direction;

typedef	struct	s_map
{
	int		**coord;
	char	***colors;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct	s_transformed_map
{
	t_fdf_vec	**coord;
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

typedef struct	s_fdf_exit_data
{
	t_fdf				*fdf;
	t_transformed_map	*transformed_map;
	int					map_fd;
	int					last_err;
}	t_exit_data;

/*	Main functions	*/
mlx_closefunc	clean_exit(t_exit_data *exit_data);
void	error_exit(t_exit_data *exit_data, char	*err_msg, int is_mlx);
t_map	parse_map(t_exit_data *exit_data);

/*	Vector/matrix rotations, transformations, projection	*/
void	rotate_along_x(t_fdf_vec *vector, float angle);
void	rotate_along_y(t_fdf_vec *vector, float angle);
void	rotate_along_z(t_fdf_vec *vector, float angle);
void	rotate_and_project(t_transformed_map *map, t_fdf *fdf,
						t_fdf_vec *vec, int *rotation_count);

/*	Matrix and vector allocation/math	*/
void	vector_by_scalar(t_fdf_vec *vector, const float scalar);
void	allocate_fdf_vector(t_fdf_vec *vector, int x, int y, int z);

/*	Map transformation	*/
t_transformed_map	*transform_map(t_fdf *fdf, int *rotation_count, t_exit_data *exit_data);

/*	Line drawing	*/
void	draw_line(t_fdf *fdf, t_dot start, t_dot end, t_colors colors);

/*	Image creation	*/
void	draw_map(t_fdf *fdf, t_transformed_map *map);
void	put_aligned_image_to_window(t_fdf *fdf);

/*	Utils	*/
int	hexstr_to_int(char *str);
void	free_2d_arr(void **arr);
int	n_to_10_convert(unsigned char *str, int str_len, int base, int sign);

/*	TEST (COMMENT THEM OUT)	*/
void	test_print_map(int **coord, int max_x, int max_y);
void	test_fdf_key_hook(mlx_key_data_t keydata, void *param);
void	test_print_fdf_vec(t_fdf_vec *vector, char *vec_name);
//void	test_move_square(t_fdf *fdf, e_action action);

#endif
