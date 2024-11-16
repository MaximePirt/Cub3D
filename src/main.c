#include "cube.h"

void	map_maker(t_map *map)
{

}

int	main(int argc, char **argv)
{
	(void)argv;
	if (argc != 2)
	{
		printf("Error: please provide a map file\n");
		return (1);
	}

	//TODO: parse map file
	//TODO: render map

	t_map map;
	map.rows = 5;
	map.cols = 5;
	map.map = (char **)malloc(sizeof(char *) * map.rows);

	return (0);
}