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
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(param);
}
