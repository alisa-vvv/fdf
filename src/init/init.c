/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   init.c                                            :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/13 14:43:21 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/13 14:52:55 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "MLX42/MLX42.h"
#include "fdf.h"
#include <fcntl.h>

// move this to a different file probably
// ,aybe not actually
void	redraw(t_fdf *fdf, t_transformed_map *map)
{
	transform_map(fdf, map);
	ft_printf("are we segging chat\n");
	draw_map(fdf, map);
	put_aligned_image_to_window(fdf);
}

void	initial_draw(t_fdf *fdf, t_exit_data *exit_data)
{
	t_transformed_map	*map;

	map = alloc_transformed_map(fdf, exit_data);
	transform_map(fdf, map);
	while (map->max_x > MAX_IMAGE_SIZE
		|| map->max_y > MAX_IMAGE_SIZE
		|| map->min_x < MIN_IMAGE_SIZE
		|| map->min_y < MIN_IMAGE_SIZE)
	{	

		fdf->param.zoom -= 5;
		transform_map(fdf, map);
		fdf->param.zoom_max = fdf->param.zoom;
	}
	exit_data->transformed_map = map;
	draw_map(fdf, map);
	put_aligned_image_to_window(fdf);
}

void	create_window(t_fdf *fdf, char *map_file, t_exit_data *exit_data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
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

	param.zoom = 7;// ZOOM_DEFAULT;
	param.zoom_max = MAX_ZOOM_DEFAULT;
	param.height_mod = HEIGHT_DEFAULT;
	param.height_mod_max = MAX_HEIGHT_DEFAULT;
	param.color_mode = from_map;
	param.rotation_count = 0;
	return (param);
}

t_fdf	*setup_fdf_data(t_exit_data *exit_data)
{
	t_fdf	*fdf;

	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		error_exit(exit_data, MALLOC_ERR, false);
	exit_data->fdf = fdf;
	fdf->param = set_parameters();
	return (fdf);
}
