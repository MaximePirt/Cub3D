#include "cube.h"

int	player_move_forward(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Moving forward\n");
	return (0);
}

int	player_move_backward(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Moving backward\n");
	return (0);
}

int	player_look_left(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Looking left\n");
	return (0);
}

int	player_look_right(t_map *map)
{
	(void)map;
	ft_fprintf(STDOUT_FILENO, "Looking right\n");
	return (0);
}