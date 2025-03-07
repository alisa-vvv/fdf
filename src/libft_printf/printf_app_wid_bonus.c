/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_app_wid_bonus.c                              :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/06 19:26:11 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 14:02:40 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static void	pad_zeroes(char *pad_str, char *conv_str, size_t pad_count)
{
	ft_memset(pad_str, '0', pad_count);
	while (*conv_str)
	{
		*(pad_str + pad_count) = *conv_str;
		pad_str++;
		conv_str++;
	}
}

static void	pad_rjust(char *pad_str, char *conv_str, size_t pad_count)
{
	size_t	i;

	i = 0;
	while (*conv_str)
	{
		pad_str[pad_count + i] = *conv_str;
		i++;
		conv_str++;
	}
	while (pad_count--)
		pad_str[pad_count] = ' ';
}

static void	pad_ljust(char *pad_str, char *conv_str, size_t pad_c, ssize_t *l)
{
	ft_memcpy(pad_str, conv_str, *l);
	ft_memset(pad_str + *l, ' ', pad_c);
}

static char	pad_decider(char *flags)
{
	char	pad;

	pad = '0';
	if (flags[2] == '.' || flags[1] != '0' || flags[3] == '-')
		pad = ' ';
	return (pad);
}

char	*app_wid(char *conv_str, size_t pad_c, ssize_t *l, char *flags)
{
	char	pad;
	char	*orig_str;
	char	*pad_str;
	size_t	new_l;

	new_l = pad_c + *l;
	pad = pad_decider(flags);
	orig_str = conv_str;
	if (conv_str[0] == '-')
		conv_str++;
	pad_str = (char *) ft_calloc(1, new_l + 1);
	if (!pad_str)
	{
		free(conv_str);
		return (NULL);
	}
	if (pad == '0')
		pad_zeroes(pad_str, conv_str, pad_c);
	else if (flags[3] == '-')
		pad_ljust(pad_str, conv_str, pad_c, l);
	else
		pad_rjust(pad_str, conv_str, pad_c);
	(*l) = new_l;
	free (orig_str);
	return (pad_str);
}
