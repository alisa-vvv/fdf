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

void	vector_by_scalar(t_fdf_vec *vector, const float scalar)
{
	vector->x *= scalar;
	vector->y *= scalar;
	vector->z *= scalar;
}

/*	Formula for mapping ranges:
*	X is for current range values, X' for desired
*	X' = X'min + (X'max - X'min) / (Xmax - Xmin) * X - Xmin
*/
void	map_to_range(t_fdf_vec *vector, int new_range[2], int old_range[2])
{
	const float	new_len = new_range[1] - new_range[0];
	const float	old_len = old_range[1] - old_range[0];
	float		new_x;
	float		new_y;
	float		new_z;

	new_x = new_range[0] + new_len / old_len * (vector->x - old_range[0]);
	new_y = new_range[0] + new_len / old_len * (vector->y - old_range[0]);
	new_z = new_range[0] + new_len / old_len * (vector->z - old_range[0]);
	vector->x = new_x;
	vector->y = new_y;
	vector->z = new_z;
}

