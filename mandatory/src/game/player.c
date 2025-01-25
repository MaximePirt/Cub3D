/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 01:50:54 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	update_player_old_pos(t_map *map)
{
	map->player.old_x = map->player.x;
	map->player.old_y = map->player.y;
	map->player.old_dir = map->player.dir;
}

int	player_look_left(t_map *map)
{
	update_player_old_pos(map);
	if (map->player.dir <= 0)
		map->player.dir += 360;
	map->player.dir -= MOUSE_SENSITIVITY;
	return (0);
}

int	player_look_right(t_map *map)
{
	update_player_old_pos(map);
	if (map->player.dir >= 360)
		map->player.dir -= 360;
	map->player.dir += MOUSE_SENSITIVITY;
	return (0);
}
