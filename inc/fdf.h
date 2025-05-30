/* ************************************************************************** */
/*                                                                            */
/*                                                       ::::::::             */
/*   fdf.h                                             :+:    :+:             */
/*                                                    +:+                     */
/*   By: avaliull <avaliull@student.codam.nl>        +#+                      */
/*                                                  +#+                       */
/*   Created: 2025/05/21 16:22:06 by avaliull     #+#    #+#                  */
/*   Updated: 2025/05/25 20:23:15 by avaliull     ########   odam.nl          */
/*                                                                            */
/* ************************************************************************** */

#ifndef FDF_H
# define FDF_H

# include "MLX42/MLX42.h"
# include "ft_printf.h"

/*	Error messages	*/
# define PARSE_ERR "Error! Parsing fail"
# define BIG_MAP_ERR "Error! Map is too big"
# define EMPTY_MAP_ERR "Error! Map is empty"
# define MALLOC_ERR "Error! malloc()"
# define DUP2_ERR "Error! dup2()"
# define FD_ERR "Error! Invalid file descriptor"
# define MLX42_ERR "Error! MLX42"

/*	Default values	*/
# define WINDOW_HEIGHT 1536
# define WINDOW_WIDTH 2048
# define MAX_IMAGE_SIZE 9500
# define MIN_IMAGE_SIZE -9500
# define MAX_MAP_SIZE 3000
# define COLOR_TEAL "0x90E4C1FF"
# define COLOR_WHITE "0xFFFFFFFF"
# define COLOR_RED "0xFF0000FF"
# define COLOR_GREEN "0x00FF00FF"
# define COLOR_BLUE "0x0000FFFF"
# define RGBA_TEAL 0x90E4C1FF
# define RGBA_WHITE 0xFFFFFFFF
# define RGBA_RED 0xFF0000FF
# define RGBA_GREEN 0x00FF00FF
# define RGBA_BLUE 0x0000FFFF
# define MAX_ZOOM_DEFAULT 300
# define MAX_HEIGHT_DEFAULT 10
# define HEIGHT_DEFAULT 6

typedef union t_rgba
{
	uint32_t	rgba;
	struct
	{
		uint8_t		a;
		uint8_t		b;
		uint8_t		g;
		uint8_t		r;
	} ;
}	t_rgba;

typedef struct s_pixel
{
	int		x;
	int		y;
	t_rgba	color;
}	t_pixel;

typedef struct s_colors
{
	char	*start;
	char	*end;
}	t_colors;

typedef struct s_fdf_vec
{
	double	x;
	double	y;
	double	z;
	char	*color;
}	t_fdf_vec;

typedef struct s_map
{
	int		**coord;
	char	***colors;
	char	***height_colors;
	int		max_x;
	int		max_y;
	int		max_z;
	int		min_z;
}	t_map;

typedef struct s_transformed_map
{
	t_fdf_vec	**coord;
	double		min_x;
	double		max_x;
	double		min_y;
	double		max_y;
}	t_transformed_map;

typedef enum t_map_color
{
	from_map,
	height_gradient,
	default_color,
	no_color,
}	t_map_color;

typedef struct s_fdf_param
{
	int			zoom;
	int			zoom_default;
	int			zoom_max;
	int			x_offset;
	int			y_offset;
	int			rotation_count;
	double		time_tracker;
	t_map_color	color_mode;
}	t_fdf_param;

typedef struct s_fdf
{
	t_fdf_param	param;
	t_map		*map;
	mlx_t		*window;
	mlx_image_t	*img;
}	t_fdf;

typedef struct s_fdf_exit_data
{
	t_fdf				*fdf;
	t_transformed_map	*transformed_map;
	char				*map_line;
	int					map_fd;
	int					last_err;
}	t_exit_data;

/*	Main functions	*/
mlx_closefunc	clean_exit(t_exit_data *exit_data);
void			error_exit(t_exit_data *exit_data, char	*err_msg, int is_mlx);
void			parse_map(t_exit_data *exit_data);

/*	Initialization	*/
void			initial_draw(t_fdf *fdf, t_exit_data *exit_data,
					t_transformed_map *map);
void			create_window(t_fdf *fdf, char *map_file,
					t_exit_data *exit_data);
void			set_exit_data(t_exit_data *exit_data, char *fd_arg);
t_fdf_param		set_parameters(void);
t_fdf			*setup_fdf_data(t_exit_data *exit_data);
/*	Parsing	*/
int				read_map(t_map *map, int map_fd, int y, t_exit_data *exit_data);
int				read_colors(char **values, char **colors, const int x);
char			**read_first_line(t_map *map, int map_fd,
					t_exit_data *exit_data);
void			add_first_line(char **line, t_map *map,
					t_exit_data *exit_data);
int				panic_free(int **coord, char ***colors, int y);

/*	Vector/matrix rotations, transformations, projection	*/
void			rotate_along_x(t_fdf_vec *vector, float angle);
void			rotate_along_y(t_fdf_vec *vector, float angle);
void			rotate_along_z(t_fdf_vec *vector, float angle);
void			project_map(t_transformed_map *map, t_fdf *fdf, t_fdf_vec *vec);

/*	Map transformation	*/
void			alloc_transformed_map(t_fdf *fdf, t_exit_data *exit_data);
void			transform_map(t_fdf *fdf, t_transformed_map *transformed_map);

/*	Rendering	*/
void			draw_map(t_fdf *fdf, t_exit_data *exit_data,
					t_transformed_map *map);
void			redraw(t_fdf *fdf, t_exit_data *exit_data,
					t_transformed_map *map);
void			put_aligned_image_to_window(t_fdf *fdf, t_exit_data *exit_data);

/*	Line drawing	*/
void			create_line(t_fdf *fdf, t_transformed_map *map,
					t_fdf_vec vec, t_fdf_vec next_vec);
void			draw_line(t_fdf *fdf, t_pixel start, t_pixel end);

/*	Controls	*/
void			fdf_key_hook(mlx_key_data_t keydata, void *param);
void			fdf_loop_hook(void *param);

/*	Utils	*/
uint32_t		hexstr_to_int(char *str, int len);

/*	TEST (COMMENT THEM OUT)	*/
//void			test_print_map(int **coord, int max_x, int max_y);
//void			test_print_fdf_vec(t_fdf_vec *vector, char *vec_name);
//void			*fake_ft_calloc(size_t nmemb, size_t size);
//void			*fake_malloc(size_t size);

#endif
