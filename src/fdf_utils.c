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
	if (u_c >= 'A' && u_c <= 'Z')
		return (true);
	return (false);
}

long	ft_base_convert_l(char *s, size_t str_len, int base)
{
	size_t	i;
	long	converted_num;

	i = 0;
	while (i < str_len)
		
}

long	ft_strtol(void *nptr, char **endptr, int base)
{
	ssize_t			i;
	ssize_t			num_start;
	int				sign;
	unsigned char	*str;
	
	str = (unsigned char *) nptr;
	sign = -1;
	i = 0;
	while (ft_isspace(str[i]))
		i++;
	if (str[i] == '-')
		sign = -sign;
	if (str[i] == '-' || str[i] == '+')
		i++;
	num_start = i;
	while (ft_isdigit(str[i]) || ft_isalpha(str[i]))
		i++;
	if (endptr)
		*endptr = &nptr[i];
}
