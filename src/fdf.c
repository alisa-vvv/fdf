#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>

// question: use struct for each individual coordinate point? feels wrong.
// alternative: use a single 3d array. then points can be found by coordinates.
// question: what is x=0? what is y=0? is it the top of the map?
// probably, feels the easiest since it's the order in which string is read.
// left to right, up to down

int		get_z(
{
	"ft_split"
	x = -1;
	while ("++x")
		z = "ft_atoi each splitted part"
		t_map->x = x;
}
void	interpret_coordinate(t_map *map, int y, char *line);
{
	int	x;
	int	z;

	while ("string is not over")
			"call get_z"
}

int ***parse_map(char *filename)
{
	const int	map_fd = open(filename, O_WRONLY);
	int			***map;
	char		*next_line;
	int			y;

	next_line = get_next_line(map_fd);
	if (!next_line)
		return (NULL);
	y = 0;
	while (next_line != NULL)
	{
		interpret_coordinate(map, y);
		y++;
		free(next_line);
		next_line = get_next_line(map_fd);
		if (!next_line)
			return (NULL);
	}
	map = NULL;
	return (map);
}

int	main(int argc, char *argv[])
{
	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	return (0);
}
