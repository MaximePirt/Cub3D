#include "cube.h"

static t_win	*ft_init_window(char *filename)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	if (win == NULL)
	{
		ft_printf("malloc error in ft_init_window\n");
		exit(0);
	}
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT,
								  filename);
	win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	return (win);
}



int	main(int argc, char **argv)
{
	t_win	*win;

	(void)argv;
	if (argc != 2)
	{
		printf("Error: please provide a map file\n");
		return (1);
	}

	//TODO: parse map file
	//TODO: render map
	win = ft_init_window(argv[1]);
	ft_init_keymap(win);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_loop(win->mlx_ptr);

	return (0);
}