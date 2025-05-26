/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   test_funcs.c                                      :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/27 16:33:58 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/21 19:30:30 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdio.h>

//void	test_print_map(int **coord, int max_x, int max_y)
//{
//	int	x;
//	int	y;
//
//	y = 0;
//	while (y <= max_y)
//	{
//		x = 0;
//		while (x <= max_x)
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
//void	*fake_malloc(size_t size)
//{
//	ft_printf("size passed to malloc: %d\n", size);
//	return (NULL);
//}
//
//void	*fake_ft_calloc(size_t nmemb, size_t size)
//{
//	ft_printf("nmemb passed to calloc: %d\n", nmemb);
//	ft_printf("size passed to calloc: %d\n", size);
//	return (NULL);
//}
//
//void	test_print_fdf_vec(t_fdf_vec *vector, char *vec_name)
//{
//	printf("\n");
//	printf("vector: %s\n", vec_name);
//	printf("x: %f\n", vector->x);
//	printf("y: %f\n", vector->y);
//	printf("z: %f\n", vector->z);
//	printf("\n\n");
//}
