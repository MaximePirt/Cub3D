#include "cube.h"

int	player_move_forward(t_map *map)
{
	double	angle_rad;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	map->player.x += cos(angle_rad) * 0.1;
	map->player.y += sin(angle_rad) * 0.1;

	return (0);
}

int	player_move_backward(t_map *map)
{
	double angle_rad;

	angle_rad = ((map->player.dir) * M_PI / 180.0);
	map->player.x -= cos(angle_rad) * 0.1;
	map->player.y -= sin(angle_rad) * 0.1;
	return (0);
}

int	player_look_left(t_map *map)
{
	if (map->player.dir <= 0)
		map->player.dir += 360;
	map->player.dir -= 2.5;
	return (0);
}

int	player_look_right(t_map *map)
{
	if (map->player.dir >= 360)
		map->player.dir -= 360;
	map->player.dir += 2.5;
	return (0);
}
