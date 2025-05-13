/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/03/07 18:05:14 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/13 15:09:02 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "ft_printf.h"

/*	Error messages	*/
# define PARSE_ERR "Error! Parsing fail"
# define MALLOC_ERR "Error! malloc()"
# define DUP2_ERR "Error! dup2()"
# define FD_ERR "Error! Invalid file descriptor"
# define MLX42_ERR "Error! MLX42"

/*	Default values	*/
# define MAX_IMAGE_SIZE 9500
# define MIN_IMAGE_SIZE -9500
# define COLOR_TEAL "0x008080FF"
# define COLOR_WHITE "0xFFFFFFFF"
# define COLOR_BLUE "0x0000FFFF"
# define COLOR_RED "0xFF0000FF"
# define RGBA_TEAL 0x008080FF
# define RGBA_WHITE 0xFFFFFFFF
# define RGBA_BLUE 0x0000FFFF
# define RGBA_RED 0xFF0000FF
# define ZOOM_DEFAULT 50
# define MAX_ZOOM_DEFAULT 100
# define MAX_HEIGHT_DEFAULT 10
# define HEIGHT_DEFAULT 6

typedef union rgba_u
{
	uint32_t	rgba;
	struct
	{
		uint8_t		a;
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
	} ;
}	rgba_u;

typedef struct	s_pixel
{
	int		x;
	int		y;
	rgba_u		color;
}	t_pixel;

typedef struct	s_colors
{
	char	*start;
	char	*end;
}	t_colors;

typedef struct	s_fdf_vec
{
	double	x;
	double	y;
	double	z;
	char	*color;
}	t_fdf_vec;

typedef enum	e_direction
{
	up,
	down,
	left,
	right,
}	e_direction;

typedef	struct	s_map
{
	int		**coord;
	char	***colors;
	rgba_u	**height_colors;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct	s_transformed_map
{
	t_fdf_vec	**coord;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
}	t_transformed_map;

typedef enum	e_map_color
{
	from_map,
	default_color,
	height,
	no_color,
	arg_color,
}	e_map_color;

typedef struct	s_fdf_param
{
	int			zoom;
	int			zoom_max;
	int			height_mod;
	int			height_mod_max;
	int			rotation_count;
	e_map_color	color_mode;
}	t_fdf_param;

typedef struct	s_fdf
{
	t_fdf_param	param;
	t_map		map;
	mlx_t		*window;
	mlx_image_t	*img;
}	t_fdf;

typedef struct	s_fdf_exit_data
{
	t_fdf				*fdf;
	t_transformed_map	*transformed_map;
	int					map_fd;
	int					last_err;
}	t_exit_data;

/*	Main functions	*/
mlx_closefunc	clean_exit(t_exit_data *exit_data);
void			error_exit(t_exit_data *exit_data, char	*err_msg, int is_mlx);
t_map			parse_map(t_exit_data *exit_data);

/*	Initialization	*/
void			initial_draw(t_fdf *fdf, t_exit_data *exit_data);
void			create_window(t_fdf *fdf, char *map_file,
					 t_exit_data *exit_data);
void			set_exit_data(t_exit_data *exit_data, char *fd_arg);
t_fdf_param		set_parameters(void);
t_fdf			*setup_fdf_data(t_exit_data *exit_data);

/*	Vector/matrix rotations, transformations, projection	*/
void	rotate_along_x(t_fdf_vec *vector, float angle);
void	rotate_along_y(t_fdf_vec *vector, float angle);
void	rotate_along_z(t_fdf_vec *vector, float angle);
void	rotate_and_project(t_transformed_map *map, t_fdf *fdf, t_fdf_vec *vec);

/*	Matrix and vector allocation/math	*/
void	vector_by_scalar(t_fdf_vec *vector, const float scalar);
void	setval_fdf_vector(t_fdf_vec *vector, int x, int y, int z);

/*	Map transformation	*/
t_transformed_map	*alloc_transformed_map(t_fdf *fdf, t_exit_data *exit_data);
void				transform_map(t_fdf *fdf, t_transformed_map *transformed_map);

/*	Line drawing	*/
void	draw_line(t_fdf *fdf, t_pixel start, t_pixel end);

/*	Image creation	*/
void	draw_map(t_fdf *fdf, t_transformed_map *map);
void	redraw(t_fdf *fdf, t_transformed_map *map);
void	put_aligned_image_to_window(t_fdf *fdf);

/*	Controls	*/
void fdf_controls(mlx_key_data_t keydata, t_fdf *fdf, t_transformed_map *map);
/*	Utils	*/
int	hexstr_to_int(char *str, int len);
void	free_2d_arr(void **arr);
int	n_to_10_convert(unsigned char *str, int str_len, int base, int sign);
int	ft_isspace(int c);

/*	TEST (COMMENT THEM OUT)	*/
void	test_print_map(int **coord, int max_x, int max_y);
void	test_fdf_key_hook(mlx_key_data_t keydata, void *param);
void	test_print_fdf_vec(t_fdf_vec *vector, char *vec_name);
//void	test_move_square(t_fdf *fdf, e_action action);

#endif
