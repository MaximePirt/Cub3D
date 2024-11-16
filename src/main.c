#include "cube.h"

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
	map = ft_init_map(10, 10);
	win = ft_init_window();
	//TODO: render map
	ft_init_keymap(win, map);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_loop(win->mlx_ptr);
	return (0);
}