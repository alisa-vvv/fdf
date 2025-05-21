/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/13 14:43:21 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/21 16:21:16 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <fcntl.h>

void	create_window(t_fdf *fdf, char *map_file, t_exit_data *exit_data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, map_file, false);
	if (!fdf->window)
		error_exit(exit_data, MLX42_ERR, true);
}

void	set_exit_data(t_exit_data *exit_data, char *fd_arg)
{
	exit_data->map_fd = -1;
	exit_data->fdf = NULL;
	exit_data->transformed_map = NULL;
	exit_data->last_err = 0;
	exit_data->map_fd = open(fd_arg, O_RDONLY);
	if (exit_data->map_fd < 0)
		error_exit(exit_data, FD_ERR, false);
}

t_fdf_param	set_parameters(void)
{
	t_fdf_param	param;

	param.zoom = MAX_ZOOM_DEFAULT;
	param.zoom_default = MAX_ZOOM_DEFAULT;
	param.zoom_max = MAX_ZOOM_DEFAULT;
	param.x_offset = 0;
	param.y_offset = 0;
	param.color_mode = from_map;
	param.rotation_count = 0;
	param.time_tracker = 0;
	return (param);
}

t_fdf	*setup_fdf_data(t_exit_data *exit_data)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) ft_calloc(1, sizeof (t_fdf));
	if (!fdf)
		error_exit(exit_data, MALLOC_ERR, false);
	fdf->param = set_parameters();
	exit_data->fdf = fdf;
	return (fdf);
}
