#include "cube.h"

int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
	{
		if (params->map->mouse_lock)
		{
			mlx_mouse_show(params->win->mlx_ptr, params->win->win_ptr);
			params->map->mouse_lock = 0;
			return (0);
		}
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
	else if (keycode == KEY_T)
		door_interact(params->map);
	else
		return (0);
	refresh(params->win, params->map);
	return (1);
}

int	action_mouse_key(int button, int x, int y, t_key_params *params)
{
	(void)x;
	(void)y;
	(void)params;

	//button 1 = left click
	//button 2 = middle click
	//button 3 = right click
	if (button == 1)
	{
		if (params->map->mouse_lock == 1)
		{
			door_interact(params->map);
		}
		else
		{
			mlx_mouse_hide(params->win->mlx_ptr, params->win->win_ptr);
			mlx_mouse_move(params->win->mlx_ptr, params->win->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
			params->map->mouse_lock = 1;
		}
	}
	return (0);
}

void	ft_init_keymap(t_key_params *params)
{
	mlx_do_key_autorepeaton(params->win->mlx_ptr);
	mlx_hook(params->win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_mouse_hook(params->win->win_ptr, action_mouse_key, params);
	mlx_hook(params->win->win_ptr, 17, 1L << 17, ft_free_program, params);
}