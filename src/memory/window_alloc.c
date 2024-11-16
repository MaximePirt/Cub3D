#include "cube.h"

t_win	*ft_init_window(void)
{
	t_win	*win;

	win = (t_win *)malloc(sizeof(t_win));
	if (win == NULL)
	{
		ft_printf("malloc error in ft_init_window\n");
		exit(0);
	}
	win->mlx_ptr = mlx_init();
	win->win_ptr = mlx_new_window(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT, "Cube 3D");
	win->img_ptr = mlx_new_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	win->img_data = mlx_get_data_addr(win->img_ptr, &win->bpp, &win->size_line, &win->endian);
	return (win);
}
