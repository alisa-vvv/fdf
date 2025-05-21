/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf_utils.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 19:26:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/21 18:34:02 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include "ft_printf.h"
#include <math.h>
#include <stdlib.h>
#include <limits.h>

int	ft_isspace(int c)
{
	unsigned char	u_c;

	u_c = (unsigned char) c;
	if ((u_c >= '\t' && u_c <= '\r') || u_c == ' ')
		return (true);
	return (false);
}

int	ft_isupper(int c)
{
	unsigned char	u_c;

	u_c = (unsigned char) c;
	if (u_c >= 'A' && u_c <= 'Z')
		return (true);
	return (false);
}

int	ft_islower(int c)
{
	unsigned char	u_c;

	u_c = (unsigned char) c;
	if (u_c >= 'a' && u_c <= 'z')
		return (true);
	return (false);
}

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

int	hexstr_to_int(char *str, int len)
{
	int		i;
	int		result;
	int		digit_base;

	digit_base = len - 1;
	i = -1;
	result = 0;
	while (++i < len)
	{
		if (ft_isdigit(str[i]))
			result += (str[i] - '0') * pow(16, digit_base);
		else if (ft_isupper(str[i]))
			result += (10 + str[i] - 'A') * pow(16, digit_base);
		else if (ft_islower(str[i]))
			result += (10 + str[i] - 'a') * pow(16, digit_base);
		digit_base--;
	}
	return (result);
}

