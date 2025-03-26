# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: avaliull <avaliull@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2025/03/07 18:02:14 by avaliull     #+#    #+#                   #
#    Updated: 2025/03/26 14:40:38 by avaliull     ########   odam.nl           #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
MAKEFLAGS =

NAME	=	fdf
CFILES	=	fdf.c\
			parsing.c\
			fdf_utils.c\
			window_controls.c\
			test_funcs.c
OFILES	= $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))

VPATH	= $(INCLUDE) $(SRCDIRS)
OBJDIR = obj
SRCDIR = src
LIBDIR = lib
SRCDIRS = $(SRCDIR)
$(LIBDIR):
	mkdir $@
$(OBJDIR):
	mkdir $@
MLX	= $(LIBDIR)/libmlx42.a -ldl -lglfw -pthread -lm
MLXDIR = $(LIBDIR)/mlx42
LIBFT_PRINTF	= $(LIBDIR)/libft_printf/libftprintf.a
LIBFT_PRINTF_DIR = $(LIBDIR)/libft_printf
INCLUDE = inc $(LIBFT_PRINTF_DIR) $(MLXDIR)/include

RM	= rm -rf
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
INPUT	= test_maps/mars.fdf

$(OBJDIR)/%.o: %.c $(INCLUDEFILES) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDE))

$(LIBFT_PRINTF):
	export CFLAGS
	$(MAKE) all -C $(LIBFT_PRINTF_DIR)

$(MLX):
	cd $(MLXDIR) ; cmake -B build ; cmake --build build  -j4
	chmod 777 $(MLXDIR)/build/libmlx42.a
	cp $(MLXDIR)/build/libmlx42.a $(LIBDIR)

$(NAME): $(OFILES) $(LIBFT_PRINTF) $(MLX)
	$(CC) $(CFLAGS) -o $@ $^ $(addprefix -I,$(INCLUDE))

#Base/project requirements
all: $(NAME)
clean: libs_clean
	$(RM) $(OFILES) $(MLXDIR)/build
fclean:	clean
	$(RM) $(NAME)
re:	fclean all

#LSP connection for neovim
clangd:
	$(MAKE) fclean
	intercept-build-14 make all
#debugging
debug: CFLAGS += -g
debug: re
gdb: debug
	gdb ./$(NAME)
test:	$(NAME)
	./$< $(INPUT)
leak:	debug
	valgrind  --suppressions=MLX42.supp -s --leak-check=full \
	--show-leak-kinds=all --track-fds=yes ./$(NAME) $(INPUT)

.PHONY:	clangd all clean fclean re libs_clean test leak debug gdb
