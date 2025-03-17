#include "fdf.h"
#include <unistd.h>
#include <fcntl.h>
#include <stdio.h>

// question: use struct for each individual coordinate point? feels wrong.
// alternative: use a single 3d array. then points can be found by coordinates.
// question: what is x=0? what is y=0? is it the top of the map?
// probably, feels the easiest since it's the order in which string is read.
// left to right, up to down
//

int	main(int argc, char *argv[])
{
	t_map	map;

	if (argc != 2)
		return (1);
	ft_printf("testrun: argc: %d, argv[1]: %s\n", argc, argv[1]);
	map = parse_map(argv[1]);
	//test_recursive_print_map(map.coord, map.max_y, map.max_x);
	free_2d_arr((void **) map.coord);
	exit(0);
}
