#include "cube.h"

int	main(int argc, char **argv)
{
//	t_win	*win;
	t_map	*map;

	(void)argv;
	if (argc != 2)
	{
		ft_printf("Error: please provide a map file\n");
		return (1);
	}
	if (parsing_map(argv[1]))
          return (1);
//    map = ft_init_map(10, 10);
//    if (!map)
//      return (1);
    map = NULL;
    if (check_map(map, argv[1]))
	{
      ft_printf("Error: invalid map\n");
      return (1);
	}

//	//TODO: parse map file
//	map = ft_init_map(10, 10);
//	win = ft_init_window();
//	//TODO: render map
//	ft_init_keymap(win, map);
//	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
//	mlx_loop(win->mlx_ptr);
	return (0);
}