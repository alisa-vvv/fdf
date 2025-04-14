/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/14 17:23:53 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"
#include <unistd.h>
#include <fcntl.h>

#include <stdio.h>
#include <math.h>

void	main_drawing_loop(t_fdf *fdf)
{
	int					rotation_count;
	t_transformed_map	*map;

	rotation_count = 0;
	map = transform_map(fdf, &rotation_count);
	draw_map(fdf, map);
	put_aligned_image_to_window(fdf);
}

void	create_window(t_fdf *fdf, char *map_file)
{
	mlx_set_setting(MLX_STRETCH_IMAGE, 0);
	fdf->window = mlx_init(2048, 1536, map_file, false);
	mlx_key_hook(fdf->window, test_fdf_key_hook, fdf);
	if (!fdf->window)
		clean_exit(fdf, -1);
}

int	main(int argc, char *argv[])
{
	int		map_fd;
	t_fdf	*fdf;
	int		zoom;

	if (argc != 2)
		return (1);
	map_fd = open(argv[1], O_RDONLY);
	if (map_fd < 0)
		clean_exit(NULL, map_fd);
	zoom = 50;
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	fdf = (t_fdf *) malloc(sizeof (t_fdf));
	if (!fdf)
		clean_exit(NULL, map_fd);
	fdf->map = parse_map(map_fd);
	fdf->zoom = zoom;
	test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1]);
	//create_map_image(fdf, zoom, old_range);
	main_drawing_loop(fdf);
	mlx_loop(fdf->window);
	clean_exit(fdf, -1);
}
