/* ************************************************************************** */
/*                                                                            */
/*                                                         ::::::::           */
/*   printf_count_wid_prec_bonus.c                       :+:    :+:           */
/*                                                      +:+                   */
/*   By: avaliull <marvin@42.fr>                       +#+                    */
/*                                                    +#+                     */
/*   Created: 2024/11/02 17:07:32 by avaliull       #+#    #+#                */
/*   Updated: 2024/11/08 13:40:59 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

static char	*num_read(ssize_t *w_p, char *start, char *end, int i)
{
	while (start != end)
	{
		if (w_p[i] == -1)
			w_p[i] = 0;
		w_p[i] = w_p[i] * 10 + *start - 48;
		start++;
	}
	w_p[i] = w_p[i] * 10 + *start - 48;
	return (start);
}

static char	*num_finder(ssize_t *w_p, char *start, char *end, int i)
{
	char	*num_end;
	char	*tmp_ptr;

	tmp_ptr = start;
	while (tmp_ptr != end)
	{
		if (ft_isdigit(*tmp_ptr))
		{
			while (tmp_ptr != end && ft_isdigit(*tmp_ptr))
			{
				num_end = tmp_ptr;
				tmp_ptr++;
			}
			tmp_ptr = num_read(w_p, start, num_end, i);
			break ;
		}
		tmp_ptr++;
	}
	return (tmp_ptr);
}

static char	*wid_counter(ssize_t *w_p, char *start, char *end, int i)
{
	char	*num_end;
	char	*tmp_ptr;

	while ((*start == '+' || *start == '-' || *start == '#'
			|| *start == ' ') && *start != '.')
		start++;
	tmp_ptr = start;
	while (tmp_ptr != end && *tmp_ptr != '.')
	{
		if (ft_isdigit(*tmp_ptr))
		{
			while (tmp_ptr != end && ft_isdigit(*tmp_ptr))
			{
				num_end = tmp_ptr;
				tmp_ptr++;
			}
			start = num_read(w_p, start, num_end, i);
			break ;
		}
		tmp_ptr++;
	}
	return (tmp_ptr);
}

static void	spec_finder(char *start, char *end, char *flags, ssize_t *w_p)
{
	while (start != end)
	{
		if (*start == '.')
		{
			if (!ft_isdigit(*(start + 1)))
				w_p[1] = -1;
			else
				num_finder(w_p, start + 1, end, 1);
			flags[2] = '.';
			return ;
		}
		start++;
	}
}

void	w_p_finder(char *start, char *end, char *f_flags, ssize_t *w_p)
{
	while (start != end && *start != '.')
	{
		if (*start == '0')
		{
			start = wid_counter(w_p, start + 1, end, 0);
			f_flags[1] = '0';
			break ;
		}
		else if (ft_isdigit(*start))
		{
			start = num_finder(w_p, start, end, 0);
			start++;
			break ;
		}
		start++;
	}
	spec_finder(start, end, f_flags, w_p);
}
