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
#include "MLX42/MLX42_Int.h"
#include <math.h>
#include <stdlib.h>
#include <errno.h>
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

int	n_to_10_convert(unsigned char *str, int str_len, int base, int sign)
{
	long	converted_value;
	int		digit_base;
	int		i;

	if (str_len > 8)
	{
		errno = ERANGE;
		return (0);
	}
	digit_base = str_len;
	converted_value = 0;
	i = 0;
	while (digit_base-- >= 0)
	{
		if (ft_isdigit(str[digit_base]))
			converted_value += (str[i] - '0') * pow(base, digit_base);
		else if (ft_isupper(str[digit_base]))
			converted_value += (10 + str[i] - 'A') * pow(base, digit_base);
		else if (ft_islower(str[digit_base]))
			converted_value += (10 + str[i] - 'a') * pow(base, digit_base);
		i++;
	}
	if (sign < 0)
		converted_value = -converted_value;
	if (converted_value > INT_MAX || converted_value < INT_MIN)
		errno = ERANGE;
	return (converted_value);
}

//long	ft_strtol(void *nptr, char **endptr, int base)
//{
//	unsigned char	*str;
//	ssize_t			i;
//	ssize_t			num_start;
//	long long		converted_value;
//	int				sign;
//	
//	str = (unsigned char *) nptr;
//	sign = -1;
//	i = 0;
//	while (ft_isspace(str[i]))
//		i++;
//	if (str[i] == '-' || str[i] == '+')
//	{
//		if (str[i] == '-')
//			sign = -sign;
//		i++;
//	}
//	if (str[i] == '0' && (str[i + 1] == 'x' || str[i + 1] == 'X'))
//		i += 2;
//	num_start = i;
//	while (ft_isdigit(str[i]) || ft_isalpha(str[i]))
//		i++;
//	converted_value = n_to_ten_convert(&str[num_start], i - num_start);
//	if (endptr)
//		*endptr = &nptr[i];
//	return ((long) converted_value);
//}
