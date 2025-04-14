/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   window_controls.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/26 14:30:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 17:22:10 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

void	clean_exit(t_fdf *fdf, int map_fd)
{
	int	exit_status;

	if (errno != 0)
	{
		perror(strerror(errno));
		exit_status = errno;
	}
	else
		exit_status = errno;
	if (fdf)
	{
		mlx_terminate(fdf->window);
		free_2d_arr((void **) fdf->map.coord);
		free(fdf);
	}
	if (map_fd > 0)
		close(map_fd);
	exit(exit_status);
}

