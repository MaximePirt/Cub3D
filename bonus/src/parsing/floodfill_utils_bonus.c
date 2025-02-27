/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill_utils_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:35:39 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:40:18 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

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
		while (j < map->size_x)
		{
			if (map->blocks[i][j].type == FLOOR
				|| map->blocks[i][j].type == DOOR)
			{
				*start_y = i;
				*start_x = j;
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
			else if (map->blocks[i][j].type == FILL
				&& map->blocks[i][j].status == 1)
				map->blocks[i][j].type = DOOR;
			j++;
		}
		i++;
	}
	return ;
}

/**
 * @brief Flood fill algorithm to fill the map
 * @param map the map
 * @return t_map*
 */
int	preptoflood(t_map *map)
{
	int	start_y;
	int	start_x;

	start_y = map->player.y;
	start_x = map->player.x;
	if (flood_fill(map, start_y, start_x))
	{
		ft_fprintf(STDERR_FILENO, "Flood fill failed\n");
		return (1);
	}
	while (check_floodfill_end(map, &start_y, &start_x))
	{
		if (flood_fill(map, start_y, start_x))
		{
			ft_fprintf(STDERR_FILENO, "Flood fill failed\n");
			return (1);
		}
	}
	restore_map(map);
	return (0);
}
