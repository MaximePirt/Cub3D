/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   keymap.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 01:50:35 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	player_movement_key(t_key_params *params, int keycode)
{
	if (keycode == KEY_W)
		player_move_forward(params->map);
	else if (keycode == KEY_S)
		player_move_backward(params->map);
	else if (keycode == KEY_D)
		player_move_left(params->map);
	else if (keycode == KEY_A)
		player_move_right(params->map);
	else
		return (0);
	return (1);
}

int	action_key(int keycode, t_key_params *params)
{
	if (keycode == KEY_ESC)
		ft_free_program(params);
	else if (player_movement_key(params, keycode))
		return (1);
	else if (keycode == KEY_ARROW_LEFT)
		player_look_left(params->map);
	else if (keycode == KEY_ARROW_RIGHT)
		player_look_right(params->map);
	else
		return (0);
	return (1);
}

void	ft_init_keymap(t_key_params *params)
{
	mlx_do_key_autorepeaton(params->win->mlx_ptr);
	mlx_hook(params->win->win_ptr, 2, 1L << 0, action_key, params);
	mlx_hook(params->win->win_ptr, 17, 1L << 17, ft_free_program, params);
}
