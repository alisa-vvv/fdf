/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf_utils.c                                       :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/09 19:26:24 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/21 19:26:22 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#include "fdf.h"
#include <math.h>

uint32_t	hexstr_to_int(char *str, int len)
{
	int			i;
	uint32_t	result;
	int			digit_base;

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

char	*get_and_trim_next_line(int fd, char *set)
{
	char	*tmp;
	char	*next_line;

	tmp = get_next_line(fd);
	next_line = ft_strtrim(tmp, set);
	if (tmp)
		free(tmp);
	return (next_line);
}
