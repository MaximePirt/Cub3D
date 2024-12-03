#include "cube.h"

static int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
	{
		ft_free_program(params);
		return (1);
	}
	if (keycode == KEY_W)
		player_move_forward(params->map);
	else if (keycode == KEY_S)
		player_move_backward(params->map);
	else if (keycode == KEY_A)
		player_look_left(params->map);
	else if (keycode == KEY_D)
		player_look_right(params->map);
	refresh(params->win, params->map);
	return (0);
}

void	ft_init_keymap(t_win *win, t_map *map)
{
	t_key_params	*params;

	params = (t_key_params *)malloc(sizeof(t_key_params));
	if (params == NULL)
	{
		ft_printf("malloc error in ft_init_keymap\n");
		exit(0);
	}
	params->win = win;
	params->map = map;
	mlx_do_key_autorepeaton(win->mlx_ptr);
	mlx_hook(win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_hook(win->win_ptr, 17, 1L << 17, ft_free_program, params);
}