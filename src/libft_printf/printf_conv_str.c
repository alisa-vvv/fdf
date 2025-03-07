/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_conv_str.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/07 13:02:28 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/07 19:44:32 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"
#include <stdlib.h>

static char	*str_not_next_var(char *flags, ssize_t *w_p, ssize_t *l)
{
	char	*conv_str;

	if ((flags[2] == '.' && w_p[1] < 6))
	{
		conv_str = ft_strdup("");
		*l = 0;
	}
	else
	{
		conv_str = ft_strdup("(null)");
		*l = 6;
	}
	if (!conv_str)
		return (NULL);
	return (conv_str);
}

static char	*str_new(char *var, char *flags, ssize_t *w_p, ssize_t *l)
{
	char	*conv_str;

	*l = ft_strlen(var);
	if (flags[2] == '.' && w_p[1] < *l)
		*l = w_p[1];
	conv_str = (char *) malloc(sizeof(char) * (*l + 1));
	if (!conv_str)
		return (NULL);
	ft_memcpy(conv_str, var, *l);
	conv_str[*l] = '\0';
	return (conv_str);
}

char	*c_str(char *var, t_plst **out_lst, char *flags, ssize_t *w_p)
{
	char	*conv_str;
	ssize_t	str_len;

	if (w_p[1] == -1)
		w_p[1] = 0;
	if (!var)
		conv_str = str_not_next_var(flags, w_p, &str_len);
	else if (*var == '\0')
	{
		conv_str = ft_strdup("");
		str_len = 0;
	}
	else
		conv_str = str_new(var, flags, w_p, &str_len);
	if (!conv_str)
		return (NULL);
	conv_str = appf_cs(conv_str, flags, w_p, &str_len);
	if (!add_str_to_list(conv_str, out_lst, str_len))
		return (NULL);
	return (conv_str);
}
