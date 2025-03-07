/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   printf_flags_bonus.c                                :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 15:47:44 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 13:40:42 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	flag_finder(char *start, char *end, char *f_flags, ssize_t *w_p)
{
	char	*flags;
	char	*tmp_start;
	int		i;

	flags = "-# +";
	tmp_start = start;
	w_p_finder(start, end, f_flags, w_p);
	i = 0;
	while (i < 4)
	{
		while (start != end)
		{
			if (*start == flags[i])
			{
				f_flags[i + 3] = *start;
				break ;
			}
			start++;
		}
		start = tmp_start;
		i++;
	}
}
