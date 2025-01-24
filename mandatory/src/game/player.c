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
//TODO: remove this function bc its only for bonus
int	door_interact(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	y = (int)ceil(map->player.y + sin(angle_rad) * 0.9) - 1;
	x = (int)ceil(map->player.x + cos(angle_rad) * 0.9) - 1;
	if (map->blocks[y][x].type == DOOR)
		map->blocks[y][x].status = !map->blocks[y][x].status;
	return (0);
}
