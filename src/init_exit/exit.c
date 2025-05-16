/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   window_controls.c                                 :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/26 14:30:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/13 17:18:52 by avaliull     ########   odam.nl          */
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

static void	free_color_map(char ***map, int max_y)
{
	int	y;

	y = -1;
	while (++y <= max_y)
		free_2d_arr((void **) map[y]);
	free(map);
}

//void fdf_controls(mlx_key_data_t keydata, t_fdf *fdf, t_transformed_map *map)
//{
//	if (keydata.key == MLX_KEY_C && keydata.action == MLX_PRESS)
//	{
//		fdf->param.color_mode++;
//		if (fdf->param.color_mode >= 4)
//			fdf->param.color_mode = 0;
//		draw_map(fdf, map);
//	}
//}

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
		if (fdf->map.colors)
			free_color_map(fdf->map.colors, fdf->map.max_y);
		free(fdf);
	}
	//int	y = -1;
	//while (++y <= fdf->map.max_y)
	//{
	//	ft_printf("%d: ", y);
	//	int	x = -1;
	//	while (++x <= fdf->map.max_x)
	//		ft_printf("%d:%s, ", x, fdf->map.colors[y][x]);
	//	ft_printf("\n");
	//}
	if (map_fd > 0)
		close(map_fd);
	exit(0);
}

