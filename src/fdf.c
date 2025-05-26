/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/25 20:33:33 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

/* ****************************************************************** */
/* 							****CONTROLS****						  */
/* 		WASD - for movement											  */
/* 		Hold Shift with WASD to move faster							  */
/* 		Left arrow, Right arrow - rotate							  */
/* 		Up Arrow, Down arrow - zoom in/out							  */
/* 		C - switch color mode										  */
/* 		F - receter image											  */
/* 		R - recenter and reestore original zoom level				  */
/* 		ESC - quit													  */
/* ****************************************************************** */

#include "fdf.h"
#include "MLX42/MLX42.h"

int	main(int argc, char *argv[])
{
	t_exit_data		exit_data;
	t_fdf			*fdf;

	if (argc != 2)
	{
		ft_putstr_fd("Error! Wrong argument count\n", STDERR_FILENO);
		exit(1);
	}
	set_exit_data(&exit_data, argv[1]);
	fdf = setup_fdf_data(&exit_data);
	parse_map(&exit_data);
	create_window(fdf, argv[1], &exit_data);
	alloc_transformed_map(fdf, &exit_data);
	initial_draw(fdf, &exit_data, exit_data.transformed_map);
	mlx_key_hook(fdf->window, fdf_key_hook, &exit_data);
	mlx_loop_hook(fdf->window, fdf_loop_hook, &exit_data);
	mlx_loop(fdf->window);
	error_exit(&exit_data, "Error! Unexpected exit", 0);
}
