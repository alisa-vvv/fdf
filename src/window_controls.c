/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   window_controls.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/26 14:30:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/26 14:39:33 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

void	clean_exit(t_fdf *fdf)
{
	int	exit_status;

	if (mlx_errno != 0)
	{
		perror(mlx_strerror(mlx_errno));
		exit_status = EXIT_FAILURE;
	}
	else
		exit_status = EXIT_SUCCESS;
	if (fdf)
	{
		mlx_terminate(fdf->window);
		free_2d_arr((void **) fdf->map.coord);
		free(fdf);
	}
	exit(exit_status);
}

void	fdf_key_hook(mlx_key_data_t keydata, void *param)
{
	t_fdf	*fdf = (t_fdf *) param;

	const int	step = 10;
	int	i;
	i = 1;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(param);
	if (keydata.key == MLX_KEY_UP && (keydata.action == MLX_PRESS
	|| keydata.action == MLX_REPEAT))
	{
		while (i++ <= step)
			move_square(fdf, up);
	}
	if (keydata.key == MLX_KEY_DOWN && (keydata.action == MLX_PRESS
	|| keydata.action == MLX_REPEAT))
		move_square(fdf, down);
	if (keydata.key == MLX_KEY_LEFT && (keydata.action == MLX_PRESS
	|| keydata.action == MLX_REPEAT))
		move_square(fdf, left);
	if (keydata.key == MLX_KEY_RIGHT && (keydata.action == MLX_PRESS
	|| keydata.action == MLX_REPEAT))
		move_square(fdf, right);
}
