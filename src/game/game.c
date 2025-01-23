/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   game.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/01 06:13:17 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	game_loop(t_key_params *params)
{
	int	x;
	int	y;

	refresh(params->win, params->map);
	if (params->map->mouse_lock)
	{
		mlx_mouse_get_pos(params->win->mlx_ptr, params->win->win_ptr, &x, &y);
		mlx_mouse_move(params->win->mlx_ptr,
			params->win->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if (x > SCREEN_WIDTH / 2)
			player_look_right(params->map);
		else if (x < SCREEN_WIDTH / 2)
			player_look_left(params->map);
	}
	return (0);
}
