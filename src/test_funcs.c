/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_funcs.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/27 16:33:58 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/27 16:42:34 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

//void	test_print_map(int **coord, int max_x, int max_y)
//{
//	int	x;
//	int	y;
//
//	y = 0;
//	while (y <= max_y)
//	{
//		x = 0;
//		while(x <= max_x)
//		{
//			ft_printf("%d ", coord[y][x]);
//			ft_putchar_fd(' ', STDOUT_FILENO);
//			x++;
//		}
//		y++;
//		ft_putchar_fd('\n', STDOUT_FILENO);
//	}
//}
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

void	test_fdf_key_hook(mlx_key_data_t keydata, void *param)
{
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		clean_exit(param);
}
