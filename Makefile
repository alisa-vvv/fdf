# **************************************************************************** #
#                                                                              #
#                                                        ::::::::              #
#    Makefile                                          :+:    :+:              #
#                                                     +:+                      #
#    By: avaliull <avaliull@student.codam.nl>        +#+                       #
#                                                   +#+                        #
#    Created: 2025/05/21 19:45:55 by avaliull     #+#    #+#                   #
#    Updated: 2025/05/25 20:27:15 by avaliull     ########   odam.nl           #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL := all
MAKEFLAGS =

NAME	=	fdf
CFILES	=	fdf.c\
			fdf_utils.c\
			init.c\
			exit.c\
			parsing_starter.c\
			parsing_first_line.c\
			parsing_loop.c\
			loop_hook.c\
			key_hook.c\
			draw_calls.c\
			image_creation.c\
			line_drawing.c\
			line_algo.c\
			coordinate_adjustments.c\
			rotations.c\
			transformed_map.c\
			test_funcs.c

OFILES	= $(addprefix $(OBJDIR)/,$(CFILES:.c=.o))

VPATH	= $(INCLUDE) $(SRCDIRS)
OBJDIR = obj
SRCDIR = src
LIBDIR = lib
INCDIR = inc
SRCDIRS = $(addprefix $(SRCDIR)/, rendering controls init_exit\
		  coordinate_manipulation map_manipulation) $(SRCDIR)
$(LIBDIR):
	mkdir -p $@
$(INCDIR):
	mkdir -p $@
MLXDIR = $(LIBDIR)/mlx42
MLX	= -L$(MLXDIR)/build/ -lmlx42 -ldl -lglfw -pthread -lm
MLXFILE = $(MLXDIR)/build/libmlx42.a
LIBFT	= $(LIBDIR)/libft_printf/libft/libft.a
LIBFT_PRINTF	= $(LIBDIR)/libft_printf/libftprintf.a
LIBFT_PRINTF_DIR = $(LIBDIR)/libft_printf
INCLUDE = $(INCDIR) $(LIBFT_PRINTF_DIR) $(MLXDIR)/include
SUBMODULES = $(LIBFT_PRINTF_DIR)/Makefile $(MLXDIR)/build

RM	= rm -rf
CC	= cc
CFLAGS	= -Wall -Wextra -Werror
INPUT	= test_maps/42.fdf

$(OBJDIR):
	mkdir -p $@
$(OBJDIR)/%.o: %.c $(INCLUDE) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@ $(addprefix -I,$(INCLUDE))

$(SUBMODULES):
	$(MAKE) submodules

$(LIBFT_PRINTF):
	$(MAKE) all -C $(LIBFT_PRINTF_DIR)

$(MLXFILE):
	$(MAKE) mlx_build

$(NAME): $(SUBMODULES) $(MLXFILE) $(LIBFT_PRINTF) $(OFILES)
	$(CC) $(CFLAGS) -o $@\
		$(OFILES) $(LIBFT_PRINTF) $(MLXFILE) $(MLX) $(addprefix -I,$(INCLUDE))

#Base/project requirements
all: $(NAME)
mlx_build:
	mkdir -p $(MLXDIR) ; cd $(MLXDIR) ;\
	cmake -B build ; cmake --build build  -j4
	chmod 777 $(MLXDIR)/build/libmlx42.a
submodules:
	git submodule update --init --recursive
libs_update:
	git submodule update --init --recursive --remote
libs_clean:
	$(RM) $(MLXDIR)/build ; $(MAKE) fclean -C $(LIBFT_PRINTF_DIR)
clean:
	$(RM) $(OFILES)
fclean:	clean libs_clean
	$(RM) $(NAME)
re:	fclean all

#LSP connection for neovim
clangd:
	$(MAKE) fclean
	intercept-build-14 make all

#debugging
debug: CFLAGS += -g
debug: clean mlx_build $(NAME)
gdb: fclean debug
	gdb ./$(NAME)
test: clean mlx_build $(NAME) run
run:
	./fdf $(INPUT)
leak:	debug
	valgrind  --suppressions=MLX42.supp -s --leak-check=full \
	--show-leak-kinds=all --track-fds=yes ./$(NAME) $(INPUT)
val:
	valgrind  --suppressions=MLX42.supp -s --leak-check=full \
	--show-leak-kinds=all --track-fds=yes ./$(NAME) $(INPUT)

.PHONY:	clangd all clean fclean re libs_clean test run leak debug gdb\
	submodules mlx_build
