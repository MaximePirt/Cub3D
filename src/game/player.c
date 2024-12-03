#include "cube.h"

int	player_move_forward(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Moving forward\n");
	map->player.x += cos(map->player.dir) * 0.1;
	map->player.y += sin(map->player.dir) * 0.1;
	return (0);
}

int	player_move_backward(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Moving backward\n");
	map->player.x -= cos(map->player.dir) * 0.1;
	map->player.y -= sin(map->player.dir) * 0.1;
	return (0);
}

int	player_look_left(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Turning left\n");
	map->player.dir -= 0.1;
	return (0);
}

int	player_look_right(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Turning right\n");
	map->player.dir += 0.1;
	return (0);
}