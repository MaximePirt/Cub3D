#include "cube.h"

static void	update_player_old_pos(t_map *map)
{
	map->player.old_x = map->player.x;
	map->player.old_y = map->player.y;
	map->player.old_dir = map->player.dir;
}

int	player_move_forward(t_map *map)
{
	double	angle_rad;
	int		x;
	int		y;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	y = (int)ceil(map->player.y + sin(angle_rad) * 0.1) - 1;
	x = (int)ceil(map->player.x + cos(angle_rad) * 0.1) - 1;
	if (map->blocks[y][x].type == FLOOR)
	{
		update_player_old_pos(map);
		map->player.x += cos(angle_rad) * 0.1;
		map->player.y += sin(angle_rad) * 0.1;
	}
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
	if (map->blocks[y][x].type == FLOOR)
	{
		update_player_old_pos(map);
		map->player.x -= cos(angle_rad) * 0.1;
		map->player.y -= sin(angle_rad) * 0.1;
	}
	return (0);
}

int	player_look_left(t_map *map)
{
	update_player_old_pos(map);
	if (map->player.dir <= 0)
		map->player.dir += 360;
	map->player.dir -= 2.5;
	return (0);
}

int	player_look_right(t_map *map)
{
	update_player_old_pos(map);
	if (map->player.dir >= 360)
		map->player.dir -= 360;
	map->player.dir += 2.5;
	return (0);
}
