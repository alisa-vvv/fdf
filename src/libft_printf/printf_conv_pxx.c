/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_pxx.c                                   :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 14:43:45 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 14:23:37 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage conversions for %p, %x, %X to string;
// The resulting string is passed to add_str_to_list for writing later;
// Return is either NULL or a ptr to the converted string for error-checking.

static int	calc_len(unsigned long long n)
{
	int	len;

	if (n == 0)
		return (1);
	len = 0;
	while (n)
	{
		len++;
		n /= 16;
	}
	return (len);
}

static char	*to_hex(unsigned long long n, char *symbols, int *len)
{
	char	*conv_str;
	int		i;

	*len += calc_len(n);
	i = *len;
	conv_str = (char *) malloc(sizeof(char) * (*len + 1));
	if (!conv_str)
		return (NULL);
	conv_str[i] = '\0';
	if (n == 0)
		conv_str[0] = '0';
	while (n)
	{
		i--;
		conv_str[i] = symbols[n % 16];
		n /= 16;
	}
	return (conv_str);
}

char	*c_hexup(unsigned long long var, t_plst **out_lst)
{
	char			*conv_str;
	int				len;

	len = 0;
	conv_str = to_hex(var, "0123456789ABCDEF", &len);
	if (!conv_str)
		return (NULL);
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}

char	*c_hexlo(unsigned long long var, t_plst **out_lst)
{
	char			*conv_str;
	int				len;

	len = 0;
	conv_str = to_hex(var, "0123456789abcdef", &len);
	if (!conv_str)
		return (NULL);
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}

char	*c_ptr(void *var, t_plst **out_lst)
{
	char				*conv_str;
	int					len;
	unsigned long long	ptr_val;

	len = 2;
	ptr_val = (unsigned long long) var;
	if (!ptr_val)
	{
		conv_str = ft_strdup("(nil)");
		if (!conv_str)
			return (NULL);
		len = 5;
	}
	else
	{
		conv_str = to_hex(ptr_val, "0123456789abcdef", &len);
		conv_str[0] = '0';
		conv_str[1] = 'x';
	}
	add_str_to_list(conv_str, out_lst, len);
	return (conv_str);
}
