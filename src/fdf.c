/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.c                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/21 14:40:37 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/13 16:34:41 by avaliull     ########   odam.nl          */
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
	ft_printf("argv[1]: %s\n", argv[1]);
	set_exit_data(&exit_data, argv[1]);
	fdf = setup_fdf_data(&exit_data);
	fdf->map = parse_map(&exit_data);
	//test_print_map(fdf->map.coord, fdf->map.max_x, fdf->map.max_y);
	create_window(fdf, argv[1], &exit_data);
	initial_draw(fdf, &exit_data);
	mlx_loop(fdf->window);
	error_exit(&exit_data, "Error! Unexpected exit", 0);
}
