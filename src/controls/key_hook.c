#include "fdf.h"

void	fdf_key_hook(mlx_key_data_t keydata, void *param)
{
	t_exit_data * const	exit_data = (t_exit_data *) param;
	t_fdf * const		fdf = exit_data->fdf;

	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(exit_data);
	if ((keydata.key == MLX_KEY_F || keydata.key == MLX_KEY_R)
		&& keydata.action == MLX_PRESS)
	{
		fdf->img->instances[0].x -= fdf->param.zoom * fdf->param.x_offset;
		fdf->img->instances[0].y -= fdf->param.zoom * fdf->param.y_offset;
		fdf->param.x_offset = 0;
		fdf->param.y_offset = 0;
		if (keydata.key == MLX_KEY_R)
		{
			fdf->param.zoom = fdf->param.zoom_default;
			redraw(fdf, exit_data, exit_data->transformed_map);
		}
	}
}
