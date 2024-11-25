#include "cube.h"

/**
 * @brief Flood fill algorithm to fill the map
 * @param map the map
 * @param x the x position
 * @param y the y position
 * @return t_map*
 */
int	flood_fill(t_map *map, int x, int y)
{
	if (!map->blocks[x][y].type || x < 0 || x >= map->size_y || y < 0
		|| y >= map->size_x || map->blocks[x][y].type == WALL
		|| map->blocks[x][y].type == FILL)
		return (0);
	if (map->blocks[x++][y].type == VOID || map->blocks[x--][y].type == VOID
		|| map->blocks[x][y++].type == VOID || map->blocks[x][y--].type == VOID)
		return (1);
	map->blocks[x][y].type = FILL;
	if (flood_fill(map, x - 1, y))
		return (1);
	if (flood_fill(map, x + 1, y))
		return (1);
	if (flood_fill(map, x, y - 1))
		return (1);
	if (flood_fill(map, x, y + 1))
		return (1);
	return (0);
}

/**
 * @brief Check if the flood fill is done
 * @param map the map
 * @param start_y the start y
 * @param start_x the start x
 * @return int
 */
int	check_floodfill_end(t_map *map, int *start_y, int *start_x)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j <= map->size_x)
		{
			if (map->blocks[i][j].type == FLOOR)
			{
				*start_y = i;
				*start_x = j;
				ft_printf("\n\nFind a pb, here is the map \n\n------\n\n");
				print_enum_map(map);
				ft_printf("\n\n");
				return (1);
			}
			j++;
		}
		i++;
	}
	return (0);
}

void	restore_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->blocks[i][j].type == FILL && map->blocks[i][j].status == 0)
				map->blocks[i][j].type = FLOOR;
			else if (map->blocks[i][j].type == FILL && map->blocks[i][j].status == 1)
				map->blocks[i][j].type = DOOR;
			j++;
		}
		i++;
	}
}

/**
 * @brief Flood fill algorithm to fill the map
 * @param map the map
 * @return t_map*
 */
int	preptoflood(t_map *map)
{
	int		component;
	int		start_y;
	int		start_x;

	start_y = map->player.y;
	start_x = map->player.x;

	ft_printf("Here is the map at the beginning\n");
	print_enum_map(map);
	if (flood_fill(map, start_y, start_x))
		{
			ft_printf("Flood fill failed\n");
			return (1);
		}	while (check_floodfill_end(map, &start_y, &start_x))
	{
		ft_printf("Flood fill GOOOOO\n");
		if (flood_fill(map, start_y, start_x))
		{
			ft_printf("Flood fill failed\n");
			return (1);
		}
		
	}
	ft_printf("Flood fill done\n");
	ft_printf("After\n");
	print_enum_map(map);
	restore_map(map);
	ft_printf("After restore\n");
	print_enum_map(map);


//	if (component != map->component_data->hm_component + map->player_data.player
//		+ map->exit_data.exit + map->gun_data.hm_gun
//		|| map->component_data->hm_component < 1)
//		exit_func(0, map, NULL, 5);
	return (0);
}