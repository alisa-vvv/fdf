# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: avaliull <avaliull@student.codam.nl>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/24 12:39:24 by avaliull          #+#    #+#              #
#    Updated: 2024/11/07 18:50:07 by avaliull         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CFILES	=	ft_printf.c\
			printf_strlist_funcs.c\
			ft_utoa.c\
			printf_conv_str.c\
			printf_conv_cidu.c\
			printf_conv_pxx.c\
			printf_flags_bonus.c\
			printf_count_wid_prec_bonus.c\
			printf_app_wid_bonus.c\
			printf_app_prec_sign_bonus.c\
			printf_appf_cs_bonus.c

OFILES	= $(CFILES:.c=.o)

LIBFT	= libft/libft.a

LIBFTDIR = libft

CC	= cc

CFLAGS	= -Wall -Wextra -Werror

RM	= rm -f

AR	= ar -rcs

LIBFTALL	= all

NAME	= libftprintf.a

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

all: $(NAME)

$(LIBFT):	
	$(MAKE) all -C $(LIBFTDIR)

$(NAME): $(OFILES) $(LIBFT)
	cp $(LIBFT) $(NAME)
	$(AR) $(NAME) $(OFILES)

libft_clean:
	$(MAKE) clean -C $(LIBFTDIR)

bonus: all

clean: libft_clean
	$(RM) $(OFILES)

fclean:	clean
	$(RM) $(NAME)

re:	fclean all

.PHONY:	all bonus clean fclean re libft_clean libft_bonus
