/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/26 15:26:12 by avaliull          #+#    #+#             */
/*   Updated: 2024/10/29 14:18:49 by avaliull         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>

static int	lenctr(long unsigned int n)
{
	int	len;

	len = 0;
	while (n)
	{
		len++;
		n /= 10;
	}
	return (len);
}

static void	utoaer(char *convstr, long unsigned int tmp_int)
{
	*convstr = '\0';
	if (tmp_int == 0)
	{
		*(convstr - 1) = '0';
		return ;
	}
	while (tmp_int)
	{
		convstr--;
		*convstr = tmp_int % 10 + 48;
		tmp_int /= 10;
	}
}

char	*ft_utoa(long unsigned int n)
{
	char				nlen;
	long unsigned int	tmp_int;
	char				*convstr;

	nlen = 0;
	tmp_int = n;
	if (n == 0)
		nlen = 1;
	else
		nlen += lenctr(tmp_int);
	convstr = (char *) malloc((nlen + 1) * sizeof(char));
	if (!convstr)
		return (NULL);
	utoaer(convstr + nlen, tmp_int);
	return (convstr);
}
