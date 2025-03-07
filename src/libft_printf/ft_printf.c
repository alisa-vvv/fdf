/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/22 15:53:21 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 13:42:32 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#include <stdarg.h>
#include <stdlib.h>
#include "ft_printf.h"

static char	*conv_chooser(char *format, int *spec_len, ssize_t *w_p)
{
	char		*found_flags;
	char		*spec_start;

	spec_start = format;
	found_flags = (char *) ft_calloc(sizeof(char), 8);
	if (!found_flags)
		return (NULL);
	ft_memset(found_flags, '=', 7);
	*spec_len = 1;
	while (*format && *format != '%' && *format != 'c' && *format != 's'
		&& *format != 'd' && *format != 'i' && *format != 'p'
		&& *format != 'u' && *format != 'x' && *format != 'X')
	{
		format++;
		(*spec_len)++;
	}
	if (*format != '%')
		flag_finder(spec_start, format, found_flags, w_p);
	found_flags[0] = *format;
	return (found_flags);
}

static char	*convert(char *flags, t_plst **out_lst, va_list f_va, ssize_t *w_p)
{
	char	*checker;

	if (*flags == '%')
		checker = c_perc(out_lst);
	else if (*flags == 'c')
		checker = c_char((int)va_arg(f_va, int), out_lst, flags, w_p);
	else if (*flags == 's')
		checker = c_str(va_arg(f_va, char *), out_lst, flags, w_p);
	else if (*flags == 'd' || *flags == 'i')
		checker = c_int(va_arg(f_va, int), out_lst, flags, w_p);
	else if (*flags == 'u')
		checker = c_uint(va_arg(f_va, unsigned int), out_lst);
	else if (*flags == 'p')
		checker = c_ptr(va_arg(f_va, void *), out_lst);
	else if (*flags == 'x')
		checker = c_hexlo(va_arg(f_va, unsigned int), out_lst);
	else if (*flags == 'X')
		checker = c_hexup(va_arg(f_va, unsigned int), out_lst);
	else
		checker = NULL;
	free(flags);
	if (!checker)
		return (NULL);
	return (checker);
}

static char	*fstr_parse(char *f_ptr, va_list f_va, t_plst **out_lst, char *str)
{
	int				spec_len;
	char			*flags;
	ssize_t			w_p[2];

	spec_len = 0;
	w_p[0] = 0;
	w_p[1] = 0;
	flags = conv_chooser(f_ptr + 1, &spec_len, w_p);
	if (*str != '\0')
	{
		if (!new_str(f_ptr, spec_len, str, out_lst))
		{
			free(flags);
			return (NULL);
		}
	}
	if (!convert(flags, out_lst, f_va, w_p))
		return (NULL);
	return (f_ptr + spec_len);
}

static int	spec_find(char **f_ptr, va_list f_va, t_plst **out_lst, char **beg)
{
	while (**f_ptr)
	{
		if (**f_ptr == '%')
		{
			*f_ptr = fstr_parse(*f_ptr, f_va, out_lst, *beg);
			if (!*f_ptr)
				return (-1);
			*beg = *f_ptr + 1;
		}
		if (**f_ptr)
			(*f_ptr)++;
	}
	return (0);
}

int	ft_printf(const char *format, ...)
{
	char			*str_start;
	va_list			f_va;
	t_plst			*out_lst;
	char			*f_ptr;

	if (!format)
		return (-1);
	out_lst = NULL;
	f_ptr = (char *) format;
	str_start = f_ptr;
	va_start(f_va, format);
	if (spec_find(&f_ptr, f_va, &out_lst, &str_start) == -1)
		return (final_gigastring_out(&out_lst, -1));
	va_end(f_va);
	if (*str_start != '\0')
	{
		if (!add_str_to_list(ft_strdup(str_start), &out_lst, f_ptr - str_start))
			return (final_gigastring_out(&out_lst, -1));
	}
	return (final_gigastring_out(&out_lst, 0));
}
