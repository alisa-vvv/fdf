/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/22 20:30:20 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"

int	main(int argc, char *argv[])
{
	t_exit_data		exit_data;
	t_fdf			*fdf;

	if (argc != 2)
		return (1);
	set_exit_data(&exit_data, argv[1]);
	(void) fdf;
	fdf = setup_fdf_data(&exit_data);
	parse_map(&exit_data);
//	create_window(fdf, argv[1], &exit_data);
//	alloc_transformed_map(fdf, &exit_data);
//	initial_draw(fdf, &exit_data, exit_data.transformed_map);
//	mlx_key_hook(fdf->window, fdf_key_hook, &exit_data);
//	mlx_loop_hook(fdf->window, fdf_loop_hook, &exit_data);
//	mlx_loop(fdf->window);
	error_exit(&exit_data, "Error! Unexpected exit", 0);
}
