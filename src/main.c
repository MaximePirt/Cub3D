#include "cube.h"

static void	fill_map_test(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (i == 0 || i == map->size_y - 1 || j == 0 || j == map->size_x - 1)
				map->blocks[i][j].type = WALL;
			else
				map->blocks[i][j].type = FLOOR;
			j++;
		}
		i++;
	}
}

int	main(int argc, char **argv)
{
	t_win	*win;
	t_map	*map;

	(void)argv;
	if (argc != 2)
	{
		printf("Error: please provide a map file\n");
		return (1);
	}

	//TODO: parse map file
	map = ft_init_map(5, 5);
	//fill_map_test(map);
	win = ft_init_window();

	load_texture(map->textures->wall_north, "./maps/wall.xpm", win->mlx_ptr);
	load_texture(map->textures->wall_south, "./maps/wall.xpm", win->mlx_ptr);
	load_texture(map->textures->wall_east, "./maps/wall.xpm", win->mlx_ptr);
	load_texture(map->textures->wall_west, "./maps/wall.xpm", win->mlx_ptr);
	load_texture(map->textures->door, "./maps/wall.xpm", win->mlx_ptr);

	//TODO: render map
	refresh(win, map);
	ft_init_keymap(win, map);
	mlx_loop(win->mlx_ptr);
	return (0);
}