/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector_matrix_math.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/09 17:23:01 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/13 18:17:29 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"

void	setval_fdf_vector(t_fdf_vec *vector, int x, int y, int z)
{
	vector->x = x;
	vector->y = y;
	vector->z = z;
}
