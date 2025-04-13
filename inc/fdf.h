/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/09 17:28:44 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "MLX42/MLX42.h"
#include "ft_printf.h"

/*	Error messages	*/
# define MALLOC_ERR "malloc()"
# define DUP2_ERR "dup2()"
# define FORK_ERR "fork()"
# define PIPE_ERR "pipe()"
# define FD_ERR "invalid fd"
# define CLOSE_ERR "close()"

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

typedef struct	s_fdf
{
	t_map	map;
	int		step;
	mlx_t	*window;
	mlx_image_t	*img;
}	t_fdf;

void	free_2d_arr(void **arr);
void	clean_exit(t_fdf *fdf);
t_map	parse_map(char *filename);
void	draw_line(t_fdf *fdf, t_dot start, t_dot end, int color);
void	rotate_along_x(t_four_vector *vector, float angle);
void	rotate_along_y(t_four_vector *vector, float angle);
void	rotate_along_z(t_four_vector *vector, float angle);

/*	Matrix and vector allocation/math	*/
void	vector_by_scalar(t_four_vector *vector, const float scalar);
void	allocate_four_vector(t_four_vector *vector, int x, int y, int z);
void	map_to_range(t_four_vector *vector, int new_range[2], int old_range[2]);

/*	TEST (COMMENT THEM OUT)	*/
void	test_print_map(int **coord, int max_x, int max_y);
void	test_fdf_key_hook(mlx_key_data_t keydata, void *param);
void	test_print_four_vector(t_four_vector *vector, char *vec_name);
//void	test_move_square(t_fdf *fdf, e_action action);

#endif
