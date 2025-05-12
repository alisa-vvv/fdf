/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/12 20:31:52 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <unistd.h>
#include <fcntl.h>
#include <limits.h>

#include <stdio.h>
#include <math.h>

void	main_drawing_loop(t_fdf *fdf, t_exit_data *exit_data)
{
	int					rotation_count;
	t_transformed_map	*map;
	//const double		max_val = INT_MAX - fdf->zoom * 4;
	//const double		min_val = INT_MIN + fdf->zoom * 4;

	rotation_count = 0;
	map = transform_map(fdf, &rotation_count, exit_data);
		printf("max x: %f\n", (map->max_x));
		printf("max y: %f\n", (map->max_y));
		printf("min x: %f\n", (map->min_x));
		printf("min y: %f\n", (map->min_y));
	while (map->max_x > MAX_IMAGE_SIZE
		|| map->max_y > MAX_IMAGE_SIZE
		|| map->min_x < MIN_IMAGE_SIZE
		|| map->min_y < MIN_IMAGE_SIZE)
	{	
		free(map);
		fdf->param.zoom -= 5;
		map = transform_map(fdf, &rotation_count, exit_data);
		fdf->param.zoom_max = fdf->param.zoom;
		printf("fdf->max_zoom: %d\n", fdf->param.zoom_max);
	}
	exit_data->transformed_map = map;
	draw_map(fdf, map);
	put_aligned_image_to_window(fdf);
}

void	create_window(t_fdf *fdf, char *map_file, t_exit_data *exit_data)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	mlx_key_hook(fdf->window, test_fdf_key_hook, exit_data);
	if (!fdf->window)
		error_exit(exit_data, MLX42_ERR, true);
}

void	set_exit_data(t_exit_data *exit_data)
{
	exit_data->map_fd = -1;
	exit_data->fdf = NULL;
	exit_data->transformed_map = NULL;
	exit_data->last_err = 0;
}

t_fdf_param	set_parameters(void)
{
	t_fdf_param	param;

	param.zoom = ZOOM_DEFAULT;
	param.zoom_max = MAX_ZOOM_DEFAULT;
	param.height_mod = HEIGHT_DEFAULT;
	param.height_mod_max = MAX_HEIGHT_DEFAULT;
	param.map_color = default_color;
	return (param);
}

int	main(int argc, char *argv[])
{
	t_exit_data		exit_data;
	t_fdf			*fdf;

	if (argc != 2)
		return (1);
	set_exit_data(&exit_data);
	exit_data.map_fd = open(argv[1], O_RDONLY);
	if (exit_data.map_fd < 0)
		error_exit(&exit_data, FD_ERR, false);
	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		error_exit(&exit_data, MALLOC_ERR, false);
	exit_data.fdf = fdf;
	fdf->param = set_parameters();
	ft_printf("where seg?\n");
	fdf->map = parse_map(&exit_data);
	exit_data.map_fd = -1;
	//test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1], &exit_data);
	main_drawing_loop(fdf, &exit_data);
	mlx_loop(fdf->window);
	mlx_close_hook(fdf->window, clean_exit(&exit_data), NULL);
}
