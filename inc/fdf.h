/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/13 14:15:36 by avaliull     ########   odam.nl          */
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


typedef enum	e_action
{
	draw,
	up,
	down,
	left,
	right,
}	e_action;

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
void	fdf_key_hook(mlx_key_data_t keydata, void *param);
void	img_test(t_fdf *fdf);
void	move_square(t_fdf *fdf, e_action action);

/*	TEST (COMMENT THEM OUT)	*/
void	test_recursive_print_map(int **coord, int y, int max_x);

#endif
