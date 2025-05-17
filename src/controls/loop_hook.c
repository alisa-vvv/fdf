#include "fdf.h"

void	zoom_projection(t_fdf *const fdf, t_exit_data *const exit_data,
					 t_transformed_map *const map)
{
	int	zoom_factor;

	if (fdf->param.time_tracker > 0.02)
	{
		zoom_factor = fdf->param.zoom / 10 + 1;
		if (mlx_is_key_down(fdf->window, MLX_KEY_UP))
		{
			if (fdf->param.zoom > fdf->param.zoom_max)
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
		redraw(fdf, exit_data, map);
		fdf->param.time_tracker = 0;
	}
}

void	rotate_projection(t_fdf *const fdf, t_exit_data *const exit_data,
				  t_transformed_map *const map)
{
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
		redraw(fdf, exit_data, map);
		fdf->param.time_tracker = 0;
	}
}

void	color_switch(t_fdf *const fdf, t_exit_data *const exit_data,
				  t_transformed_map *const map)
{
	if (fdf->param.time_tracker > 0.2)
	{
		fdf->param.color_mode++;
		if (fdf->param.color_mode > 2)
			fdf->param.color_mode = 0;
		redraw(fdf, exit_data, map);
		fdf->param.time_tracker = 0;
	}
}

void	move_image(t_fdf *const fdf, int move_speed)
{
	if (fdf->param.time_tracker > 0.04)
	{
		if (mlx_is_key_down(fdf->window, MLX_KEY_W))
		{
			fdf->img->instances[0].y += fdf->param.zoom * move_speed;
			fdf->param.y_offset += move_speed;
		}
		if (mlx_is_key_down(fdf->window, MLX_KEY_S))
		{
			fdf->img->instances[0].y -= fdf->param.zoom * move_speed;
			fdf->param.y_offset -= move_speed;
		}
		if (mlx_is_key_down(fdf->window, MLX_KEY_A))
		{
			fdf->img->instances[0].x += fdf->param.zoom * move_speed;
			fdf->param.x_offset += move_speed;
		}
		if (mlx_is_key_down(fdf->window, MLX_KEY_D))
		{
			fdf->img->instances[0].x -= fdf->param.zoom * move_speed;
			fdf->param.x_offset -= move_speed;
		}
		fdf->param.time_tracker = 0;
	}
}

void	fdf_loop_hook(void *param)
{
	t_exit_data * const	exit_data = (t_exit_data *) param;
	t_fdf * const		fdf = exit_data->fdf;

	fdf->param.time_tracker += fdf->window->delta_time;
	if (mlx_is_key_down(fdf->window, MLX_KEY_C))
		color_switch(fdf, exit_data, exit_data->transformed_map);
	if (mlx_is_key_down(fdf->window, MLX_KEY_RIGHT) ||
		mlx_is_key_down(fdf->window, MLX_KEY_LEFT))
		rotate_projection(fdf, exit_data, exit_data->transformed_map);
	if (mlx_is_key_down(fdf->window, MLX_KEY_UP)
	|| mlx_is_key_down(fdf->window, MLX_KEY_DOWN))
		zoom_projection(fdf, exit_data, exit_data->transformed_map);
	if (mlx_is_key_down(fdf->window, MLX_KEY_W)
	|| mlx_is_key_down(fdf->window, MLX_KEY_S)
	|| mlx_is_key_down(fdf->window, MLX_KEY_A)
	|| mlx_is_key_down(fdf->window, MLX_KEY_D))
	{
		if (mlx_is_key_down(fdf->window, MLX_KEY_LEFT_SHIFT))
			move_image(fdf, 8);
		else
			move_image(fdf, 2);
	}
}
