/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   testfuncs.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/13 14:14:39 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/13 14:15:08 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	test_recursive_print_map(int **coord, int y, int max_x)
{
	int	x;

	while (y--)
	{
		x = 0;
		while(x <= max_x)
		{
			ft_printf("%d ", coord[y][x]);
			ft_putchar_fd(' ', STDOUT_FILENO);
			x++;
		}
		ft_putchar_fd('\n', STDOUT_FILENO);
	}
}

