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

void	test_print_fdf_vec(t_fdf_vec *vector, char *vec_name)
{
	printf("\n");
	printf("vector: %s\n", vec_name);
	printf("x: %f\n", vector->x);
	printf("y: %f\n", vector->y);
	printf("z: %f\n", vector->z);
	printf("\n\n");
}

//
//
//#ifndef	SQUARE_SIZE
//# define SQUARE_SIZE 70
//#endif
//
//void	test_move_square(t_fdf *fdf, e_action action)
//{
//	const int	step = 1;
//	int	i;
//	i = 1;
//	if (action == up)
//	{
//		while (i++ <= step)
//			fdf->img->instances[0].y -= 1;
//	}
//	else if (action == down)
//		fdf->img->instances[0].y += 10;
//	else if (action == left)
//		fdf->img->instances[0].x -= 10;
//	else if (action == right)
//		fdf->img->instances[0].x += 10;
//}
//
//void	test_draw_square(t_fdf *fdf)
//{
//	int	x = 30;
//	int	y = 30;
//
//	fdf->img = mlx_new_image(fdf->window, 256, 256);
//	if (!fdf->img)
//	{
//		fdf->img = NULL;
//		return ;
//	}
//	while (y <= 100)
//	{
//		while (x <= 100)
//		{
//			mlx_put_pixel(fdf->img, x, y, 0x008080FF);
//			x++;
//		}
//		x = 30;
//		y++;
//	}
//}

void	zoom_projection(t_fdf *const fdf, t_transformed_map *const map)
{
	int	zoom_factor;

	if (fdf->param.time_tracker > 0.02)
	{
		zoom_factor = fdf->param.zoom / 10 + 1;
		if (mlx_is_key_down(fdf->window, MLX_KEY_UP))
		{
			if (fdf->param.zoom == fdf->param.zoom_max)
				return ;
			fdf->param.zoom = fdf->param.zoom + zoom_factor;
			if (fdf->param.zoom > fdf->param.zoom_max)
				fdf->param.zoom = fdf->param.zoom_max;
		}
		else if (mlx_is_key_down(fdf->window, MLX_KEY_DOWN))
		{
			if (fdf->param.zoom == 1)
				return ;
			fdf->param.zoom = fdf->param.zoom - zoom_factor;
			if (fdf->param.zoom < 1)
				fdf->param.zoom = 1;
		}
		redraw(fdf, map);
		fdf->param.time_tracker = 0;
	}
}

void	rotate_projection(t_fdf *const fdf,
				  t_transformed_map *const map)
{
	printf("fdf->window->delta_time: %f\n", fdf->window->delta_time);
	printf("tracker: %f\n", fdf->param.time_tracker);
	if (fdf->param.time_tracker > 0.1)
	{
		if (mlx_is_key_down(fdf->window, MLX_KEY_RIGHT))
			fdf->param.rotation_count++;
		else if (mlx_is_key_down(fdf->window, MLX_KEY_LEFT))
			fdf->param.rotation_count--;
		if (fdf->param.rotation_count > 3)
			fdf->param.rotation_count = 0;
		else if (fdf->param.rotation_count < 0)
			fdf->param.rotation_count = 3;
		redraw(fdf, map);
		fdf->param.time_tracker = 0;
	}
}

void	color_switch(t_fdf *const fdf, t_transformed_map *const map)
{
	if (fdf->param.time_tracker > 0.2)
	{
		fdf->param.color_mode++;
		if (fdf->param.color_mode >= 4)
			fdf->param.color_mode = 0;
		redraw(fdf, map);
		fdf->param.time_tracker = 0;
	}
}

void	move_image(t_fdf *const fdf)// t_transformed_map *const map)
{
	(void) fdf;
//	if (fdf->param.time_tracker > 0.1)
//	{
//		if (mlx_is_key_down(fdf->window, MLX_KEY_W))
//			fdf->img->instances->y += fdf->img->height / 50;
//		if (mlx_is_key_down(fdf->window, MLX_KEY_S))
//			fdf->img->instances->y -= fdf->img->height / 50;
//		if (mlx_is_key_down(fdf->window, MLX_KEY_A))
//			fdf->img->instances->x += fdf->img->width / 50;
//		if (mlx_is_key_down(fdf->window, MLX_KEY_D))
//			fdf->img->instances->x -= fdf->img->width / 50;
//		ft_printf("x: %d\n", fdf->img->instances->x);
//		ft_printf("width: %d\n", fdf->img->width);
//		ft_printf("y: %d\n", fdf->img->instances->y);
//		ft_printf("height: %d\n", fdf->img->height);
//		fdf->param.x_offset = fdf->img->instances->x / fdf->param.zoom;
//		fdf->param.y_offset = fdf->img->instances->y / fdf->param.zoom;
//		fdf->param.time_tracker = 0;
//	}
}

void	test_fdf_key_hook(mlx_key_data_t keydata, void *param)
{
	//t_exit_data * const	exit_data = (t_exit_data *) param;
	//t_fdf * const		fdf = exit_data->fdf;

		if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
			clean_exit(param);
}

void	test_loop_hook(void *param)
{
	t_exit_data * const	exit_data = (t_exit_data *) param;
	t_fdf * const		fdf = exit_data->fdf;

	fdf->param.time_tracker += fdf->window->delta_time;
		if (mlx_is_key_down(fdf->window, MLX_KEY_C))
			color_switch(fdf, exit_data->transformed_map);
		if (mlx_is_key_down(fdf->window, MLX_KEY_RIGHT) ||
			mlx_is_key_down(fdf->window, MLX_KEY_LEFT))
			rotate_projection(fdf, exit_data->transformed_map);
		//if ((keydata.key == MLX_KEY_RIGHT || keydata.key == MLX_KEY_LEFT)
		//	&& (keydata.action == MLX_PRESS))// || keydata.action == MLX_REPEAT))
		if (mlx_is_key_down(fdf->window, MLX_KEY_UP)
		|| mlx_is_key_down(fdf->window, MLX_KEY_DOWN))
			zoom_projection(fdf, exit_data->transformed_map);
		if (mlx_is_key_down(fdf->window, MLX_KEY_W)
		|| mlx_is_key_down(fdf->window, MLX_KEY_S)
		|| mlx_is_key_down(fdf->window, MLX_KEY_A)
		|| mlx_is_key_down(fdf->window, MLX_KEY_D))
			move_image(fdf);
}
