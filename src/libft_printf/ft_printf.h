/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.h                                         :+:    :+:           */
/*                                                    +:+ +:+         +:+     */
/*   By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/24 12:33:13 by avaliull          #+#    #+#             */
/*   Updated: 2024/11/08 14:42:16 by avaliull       ########   odam.nl        */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_PRINTF_H
# define FT_PRINTF_H

# include <stddef.h>
# include <unistd.h>
# include "libft/libft.h"

typedef struct printf_lst
{
	char				*string;
	int					size;
	struct printf_lst	*next;
}						t_plst;

/*	PRIMARY FUNCTIONS	*/
int			ft_printf(const char *format, ...);

/*	LIST MANIPULATION FUNCTIONS	*/
char		*new_str(char *format, int spec_len, char *start, t_plst **out_lst);
t_plst		*add_str_to_list(char *str_start, t_plst **out_lst, int len);
int			final_gigastring_out(t_plst **out_lst, int err_ovrr);

/*	CONVERSION FUNCTIONS	*/
char		*ft_utoa(unsigned long long n);
char		*c_perc(t_plst **out_lst);
char		*c_str(char *var, t_plst **out_lst, char *flags, ssize_t *w_p);
char		*c_char(int var, t_plst **out_lst, char *flags, ssize_t *w_p);
char		*c_int(int var, t_plst **out_lst, char *flags, ssize_t *w_p);
char		*c_uint(unsigned long long var, t_plst **out_lst);
char		*c_hexup(unsigned long long var, t_plst **out_lst);
char		*c_hexlo(unsigned long long var, t_plst **out_lst);
char		*c_ptr(void *var, t_plst **out_lst);

/*	BONUS FUNCTIONS	*/
void		flag_finder(char *start, char *end, char *f_flags, ssize_t *w_p);
void		w_p_finder(char *start, char *end, char *f_flags, ssize_t *w_p);
char		*appf_cs(char *conv_str, char *flags, ssize_t *w_p, ssize_t *l);
char		*appf_di(char *conv_str, char *flags, ssize_t *w_p, ssize_t *l);
char		*app_wid(char *conv_str, size_t pad_c, ssize_t *l, char *flags);
char		check_sign(char *str, char *flags);
char		*app_prec(char *conv_str, size_t zero_count, ssize_t *l, char neg);
char		*app_sign(char *conv_str, ssize_t *l, char sign);

#endif
