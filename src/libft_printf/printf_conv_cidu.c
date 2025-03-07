/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_cidu.c                                  :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 13:03:35 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 14:06:56 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

// The following functions manage conversions for %c, %%, %i to string;
// After conversion, functions to apply bonus flags and manage width are called;
// The resulting strings are passed to add_str_to_list for writing later;
// Return is either NULL or the ptr to converted string for error-checking.

char	*c_perc(t_plst **out_lst)
{
	char	*conv_str;

	conv_str = (char *) malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = '%';
	conv_str[1] = '\0';
	if (!add_str_to_list(conv_str, out_lst, 1))
		return (NULL);
	return (conv_str);
}

char	*c_char(int var, t_plst **out_lst, char *flags, ssize_t *w_p)
{
	char	*conv_str;
	ssize_t	str_len;

	conv_str = (char *)malloc (sizeof(char) * 2);
	if (!conv_str)
		return (NULL);
	conv_str[0] = (char)var;
	conv_str[1] = '\0';
	str_len = 1;
	conv_str = appf_cs(conv_str, flags, w_p, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}

char	*c_int(int var, t_plst **out_lst, char *flags, ssize_t *w_p)
{
	char	*conv_str;
	ssize_t	str_len;

	conv_str = ft_itoa(var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	conv_str = appf_di(conv_str, flags, w_p, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}

char	*c_uint(unsigned long long var, t_plst **out_lst)
{
	char	*conv_str;
	int		str_len;

	conv_str = ft_utoa(var);
	if (!conv_str)
		return (NULL);
	str_len = ft_strlen(conv_str);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}
