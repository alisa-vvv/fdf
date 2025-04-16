/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   window_controls.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/26 14:30:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/15 18:45:25 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <stdio.h>
#include <errno.h>
#include <unistd.h>
#include <string.h>

void	error_exit(t_exit_data *exit_data, char	*err_msg, int is_mlx)
{
	if (is_mlx == true)
	{
		exit_data->last_err = mlx_errno;
		ft_putstr_fd(err_msg, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
		ft_putstr_fd((char *) mlx_strerror(mlx_errno), STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
	else
	{
		exit_data->last_err = errno;
		perror(err_msg);
	}
	clean_exit(exit_data);
}

mlx_closefunc	clean_exit(t_exit_data *exit_data)
{

	t_fdf				*fdf;
	t_transformed_map	*transformed_map;
	int					map_fd;

	fdf = exit_data->fdf;
	transformed_map = exit_data->transformed_map;
	map_fd = exit_data->map_fd;
	ft_printf("exit func called\n");
	if (transformed_map)
	{
		free_2d_arr((void **) transformed_map->coord);
		free(transformed_map);
	}
	if (fdf)
	{
		if (fdf->window)
			mlx_terminate(fdf->window);
		free_2d_arr((void **) fdf->map.coord);
		free(fdf);
	}
	if (map_fd > 0)
		close(map_fd);
	exit(0);
}

