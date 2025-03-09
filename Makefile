# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: avaliull <avaliull@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2025/03/07 18:02:14 by avaliull     #+#    #+#                   #
#    Updated: 2025/03/07 18:03:36 by avaliull     ########   odam.nl           #
#                                                                              #
# **************************************************************************** #

MAKEFLAGS	= -s

CFILES	=	fdf.c\
			parsing.c\
			fdf_utils.c

OBJDIR = obj
SRCDIR = src
SRCDIRS = $(SRCDIR)

OFILES	= $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))

VPATH	= $(INCLUDE) $(SRCDIRS)

LIBFT_PRINTF	= $(SRCDIR)/libft_printf/libftprintf.a
LIBFT_PRINTF_DIR = $(SRCDIR)/libft_printf

INCLUDEFILES = fdf.h
INCLUDE = inc $(LIBFT_PRINTF_DIR)

NAME	= fdf

RM	= rm -f

CC	= cc
CFLAGS	= -Wall -Wextra -Werror
INPUT	= test_maps/mars.fdf

clangd:
	$(MAKE) fclean
	intercept-build-14 make all

$(OBJDIR):
	mkdir $@
$(OBJDIR)/%.o: %.c $(INCLUDEFILES) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDE))

$(LIBFT_PRINTF):
	export CFLAGS
	$(MAKE) all -C $(LIBFT_PRINTF_DIR)

$(NAME): $(OFILES) $(LIBFT_PRINTF)
	$(CC) $(CFLAGS) -o $@ $^ $(addprefix -I,$(INCLUDE))

all: $(NAME)

libs_clean:
	$(MAKE) clean -C $(LIBFT_PRINTF_DIR)
clean: libs_clean
	$(RM) $(OFILES)
fclean:	clean
	$(RM) $(NAME)

re:	fclean all

debug: CFLAGS += -g
debug: re

gdb: debug
	gdb ./$(NAME)

test:	$(NAME)
	./$< $(INPUT)

leak:	debug
	valgrind -s --leak-check=full --show-leak-kinds=all \
	--track-fds=yes ./$(NAME) $(INPUT)

.PHONY:	clangd all clean fclean re libs_clean test leak debug gdb
