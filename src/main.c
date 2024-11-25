#include "cube.h"

//static void	fill_map_test(t_map *map)
//{
//	int	i;
//	int	j;
//
//	i = 0;
//	while (i < map->size_y)
//	{
//		j = 0;
//		while (j < map->size_x)
//		{
//			if (i == 0 || i == map->size_y - 1 || j == 0 || j == map->size_x - 1)
//				map->blocks[i][j].type = WALL;
//			else
//				map->blocks[i][j].type = FLOOR;
//			j++;
//		}
//		i++;
//	}
//}

int	main(int argc, char **argv)
{
	t_win	*win;
	t_map	*map;
    char	**images;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error: please provide a map file\n");
		return (1);
	}
	if (parsing_map(argv[1]))
          return (1);
	map = NULL;
    images = ft_calloc(sizeof (char *), 8);
	if (check_map(map, argv[1], &images) == 1)
	{
      ft_printf("Error: invalid map\n");
      return (1);
	}
//    for (int i = 0; images[i]; i++)
//    {
//        if (images[i] == NULL)
//        {
//            ft_printf("Error: missing texture at index [%d]\n Here is the tab\n", i);
//            for (int j = 0; j < 8; j++)
//            {
//                ft_putstr_fd(images[j], 1);
//            }
//            return (1);
//        }
//        ft_putstr_fd(images[i], 1);
//    }
    ft_tabfree(images);


//	win = ft_init_window();
//
//	load_texture(map->textures->wall_north, "./maps/wall.xpm", win->mlx_ptr);
//	load_texture(map->textures->wall_south, "./maps/wall.xpm", win->mlx_ptr);
//	load_texture(map->textures->wall_east, "./maps/wall.xpm", win->mlx_ptr);
//	load_texture(map->textures->wall_west, "./maps/wall.xpm", win->mlx_ptr);
//	load_texture(map->textures->door, "./maps/wall.xpm", win->mlx_ptr);
//
//	//TODO: render map
//	refresh(win, map);
//	ft_init_keymap(win, map);
//	mlx_loop(win->mlx_ptr);

	return (0);
}