/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player_movement.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:43:16 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

int	player_move_forward(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	y = (int)ceil(map->player.y + sin(angle_rad) * 0.1) - 1;
	x = (int)ceil(map->player.x + cos(angle_rad) * 0.1) - 1;
	if (x <= 0 || y <= 0 || x >= map->size_x - 1 || y >= map->size_y - 1)
		return (0);
	update_player_old_pos(map);
	map->player.x += cos(angle_rad) * 0.1;
	map->player.y += sin(angle_rad) * 0.1;
	return (0);
}

int	player_move_backward(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	y = (int)ceil(map->player.y - sin(angle_rad) * 0.1) - 1;
	x = (int)ceil(map->player.x - cos(angle_rad) * 0.1) - 1;
	if (x <= 0 || y <= 0 || x >= map->size_x - 1 || y >= map->size_y - 1)
		return (0);
	update_player_old_pos(map);
	map->player.x -= cos(angle_rad) * 0.1;
	map->player.y -= sin(angle_rad) * 0.1;
	return (0);
}

int	player_move_left(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir + 90) * M_PI / 180.0);
	y = (int)ceil(map->player.y + sin(angle_rad) * 0.1) - 1;
	x = (int)ceil(map->player.x + cos(angle_rad) * 0.1) - 1;
	if (x <= 0 || y <= 0 || x >= map->size_x - 1 || y >= map->size_y - 1)
		return (0);
	update_player_old_pos(map);
	map->player.x += cos(angle_rad) * 0.1;
	map->player.y += sin(angle_rad) * 0.1;
	return (0);
}

int	player_move_right(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir - 90) * M_PI / 180.0);
	y = (int)ceil(map->player.y + sin(angle_rad) * 0.1) - 1;
	x = (int)ceil(map->player.x + cos(angle_rad) * 0.1) - 1;
	if (x <= 0 || y <= 0 || x >= map->size_x - 1 || y >= map->size_y - 1)
		return (0);
	update_player_old_pos(map);
	map->player.x += cos(angle_rad) * 0.1;
	map->player.y += sin(angle_rad) * 0.1;
	return (0);
}
