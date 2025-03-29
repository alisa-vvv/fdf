/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/27 17:23:29 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

#include "MLX42/MLX42.h"
#include "ft_printf.h"

# define MALLOC_ERR "malloc()"
# define DUP2_ERR "dup2()"
# define FORK_ERR "fork()"
# define PIPE_ERR "pipe()"
# define FD_ERR "invalid fd"
# define CLOSE_ERR "close()"

//typedef enum	e_action
//{
//	draw,
//	up,
//	down,
//	left,
//	right,
//}	e_action;
//
typedef struct	s_dot
{
	int	x;
	int	y;
}	t_dot;

typedef struct	s_vector_4
{
	int	x;
	int	y;
	int	z;
	int	i;
}	t_vector_4;


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
}	t_map;

typedef struct	s_fdf
{
	t_map	map;
	mlx_t	*window;
	mlx_image_t	*img;
	int		x_zero;
	int		y_zero;
}	t_fdf;

void	free_2d_arr(void **arr);
void	clean_exit(t_fdf *fdf);
t_map	parse_map(char *filename);

/*	TEST (COMMENT THEM OUT)	*/
void	test_print_map(int **coord, int max_x, int max_y);
void	test_fdf_key_hook(mlx_key_data_t keydata, void *param);
//void	test_move_square(t_fdf *fdf, e_action action);

#endif
