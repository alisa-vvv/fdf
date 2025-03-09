/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   utils.c                                           :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 19:26:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/03/09 19:27:38 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <stdlib.h>

void	free_2d_arr(void **arr)
{
	int	i;

	if (arr)
	{
		i = -1;
		while (arr[++i])
			free(arr[i]);
		free(arr);
	}
}

