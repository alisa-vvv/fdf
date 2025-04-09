/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   vector_matrix_math.c                              :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/09 17:23:01 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/09 17:27:15 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

// Formula for mapping ranges:
// X is for current range values, X' for desired
// X' = X'min + (X'max - X'min) / (Xmax - Xmin) * X - Xmin

void	allocate_four_vector(t_four_vector *vector, int x, int y, int z)
{
	const int	step = 50;

	vector->x = x * step;
	vector->y = y * step;
	vector->z = z * sqrt(step);
	vector->w = 1;
}

void	vector_by_scalar(t_four_vector *vector, const float scalar)
{
	vector->x *= scalar;
	vector->y *= scalar;
	vector->z *= scalar;
}

void	map_to_range(t_four_vector *vector, int new_range[2], int old_range[2])
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
	vector->w = 1;
}

