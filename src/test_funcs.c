/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_funcs.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/27 16:33:58 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/15 17:45:26 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

void	test_print_map(int **coord, int max_x, int max_y)
{
	int	x;
	int	y;

	y = 0;
	while (y <= max_y)
	{
		x = 0;
		while(x <= max_x)
		{
			ft_printf("%d ", coord[y][x]);
			ft_putchar_fd(' ', STDOUT_FILENO);
			x++;
		}
		y++;
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

void	*fake_malloc(size_t size)
{
	ft_printf("size passed to malloc: %d\n", size);
	return (NULL);
}

void	*fake_ft_calloc(size_t nmemb, size_t size)
{
	ft_printf("nmemb passed to calloc: %d\n", nmemb);
	ft_printf("size passed to calloc: %d\n", size);
	return (NULL);
}

void	test_print_fdf_vec(t_fdf_vec *vector, char *vec_name)
{
	printf("\n");
	printf("vector: %s\n", vec_name);
	printf("x: %f\n", vector->x);
	printf("y: %f\n", vector->y);
	printf("z: %f\n", vector->z);
	printf("\n\n");
}
//	void	test_fdf_key_hook(mlx_key_data_t keydata, void *param)
//	{
//		t_exit_data * const	exit_data = (t_exit_data *) param;
//		t_fdf * const		fdf = exit_data->fdf;
//	
//		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
//			clean_exit(exit_data);
//		if (keydata.key == MLX_KEY_F && keydata.action == MLX_PRESS)
//		{
//			fdf->img->instances[0].x -= fdf->param.zoom * fdf->param.x_offset;
//			fdf->img->instances[0].y -= fdf->param.zoom * fdf->param.y_offset;
//			fdf->param.x_offset = 0;
//			fdf->param.y_offset = 0;
//		}
//	}
//	
//	void	test_loop_hook(void *param)
//	{
//		t_exit_data * const	exit_data = (t_exit_data *) param;
//		t_fdf * const		fdf = exit_data->fdf;
//	
//		fdf->param.time_tracker += fdf->window->delta_time;
//		if (mlx_is_key_down(fdf->window, MLX_KEY_C))
//			color_switch(fdf, exit_data->transformed_map);
//		if (mlx_is_key_down(fdf->window, MLX_KEY_RIGHT) ||
//			mlx_is_key_down(fdf->window, MLX_KEY_LEFT))
//			rotate_projection(fdf, exit_data->transformed_map);
//		if (mlx_is_key_down(fdf->window, MLX_KEY_UP)
//		|| mlx_is_key_down(fdf->window, MLX_KEY_DOWN))
//			zoom_projection(fdf, exit_data->transformed_map);
//		if (mlx_is_key_down(fdf->window, MLX_KEY_W)
//		|| mlx_is_key_down(fdf->window, MLX_KEY_S)
//		|| mlx_is_key_down(fdf->window, MLX_KEY_A)
//		|| mlx_is_key_down(fdf->window, MLX_KEY_D))
//		{
//			if (mlx_is_key_down(fdf->window, MLX_KEY_LEFT_SHIFT))
//				move_image(fdf, 8);
//			else
//				move_image(fdf, 2);
//		}
//	}
