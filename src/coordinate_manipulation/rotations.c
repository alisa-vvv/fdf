/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   rotations.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/04/05 13:40:21 by avaliull     #+#    #+#                  */
/*   Updated: 2025/04/05 14:18:51 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

/*	This performs the following rotation matrix multiplicaton:
*	{	1 		0, 				0 			}	{x}
*	{	0		cos(angle)		-sin(angle)	}	{y}
*	{	0		sin(angle)		cos(angle)	}	{z}
*/
void	rotate_along_x(t_fdf_vec *vector, float angle)
{
	const float	angle_rad = M_PI / 180 * angle;
	const float	cos_angle = cos(angle_rad);
	const float	sin_angle = sin(angle_rad);
	float		dot_product_y;
	float		dot_product_z;

	dot_product_y = vector->y * cos_angle + vector->z * -sin_angle;
	dot_product_z = vector->y * sin_angle + vector->z * cos_angle;
	vector->y = dot_product_y;
	vector->z = dot_product_z;
}

/*	This performs the following rotation matrix multiplicaton:
*	{	cos(angle)		0		sin(angle) 	}	{x}
*	{	0				1		0			}	{y}
*	{	-sin(angle)		0		cos(angle)	}	{z}
*/
void	rotate_along_y(t_fdf_vec *vector, float angle)
{
	const float	angle_rad = M_PI / 180 * angle;
	const float	cos_angle = cos(angle_rad);
	const float	sin_angle = sin(angle_rad);
	float		dot_product_x;
	float		dot_product_z;

	dot_product_x = vector->x * cos_angle + vector->z * sin_angle;
	dot_product_z = vector->x * -sin_angle + vector->z * cos_angle;
	vector->x = dot_product_x;
	vector->z = dot_product_z;
}

/*	This performs the following rotation matrix multiplicaton:
*	{	cos(angle)		-sin(angle)		0	}	{x}
*	{	sin(angle)		cos(angle)		0	}	{y}
*	{	0				0				1	}	{z}
*/
void	rotate_along_z(t_fdf_vec *vector, float angle)
{
	const float	angle_rad = M_PI / 180 * angle;
	const float	cos_angle = cos(angle_rad);
	const float	sin_angle = sin(angle_rad);
	float		dot_product_x;
	float		dot_product_y;

	dot_product_x = vector->x * cos_angle + vector->y * -sin_angle;
	dot_product_y = vector->x * sin_angle + vector->y * cos_angle;
	vector->x = dot_product_x;
	vector->y = dot_product_y;
}
