/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   copy_tab_to_map.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:37:19 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/27 00:49:15 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Check if the block is a wall, floor or door
 * @param to_copy the parse map
 * @param map the map
 * @param i the i index
 * @param j the j index
 * @return int 1 if a floor or a door, 0 else
 */
int	is_wall_floor_door(t_parse_map *to_copy, t_map *map, int i, int j)
{
	if (i < 0 || i >= map->size_y || j < 0 || j >= map->size_x)
		return (0);
	map->blocks[i][j].status = 0;
	if (to_copy->blocks[j] == 'D')
	{
		map->blocks[i][j].type = DOOR;
		map->blocks[i][j].status = 1;
		return (1);
	}
	if (to_copy->blocks[j] == '1')
	{
		map->blocks[i][j].type = WALL;
		return (1);
	}
	if (to_copy->blocks[j] == '0')
	{
		map->blocks[i][j].type = FLOOR;
		return (1);
	}
	if (to_copy->blocks[j] == ' ')
	{
		map->blocks[i][j].type = VOID;
		return (1);
	}
	return (0);
}

/**
 * @brief Check if the block is a player
 * @param to_copy the parse map
 * @param map the map
 * @param i the i index
 * @param j the j index
 * @return int 1 if a player, 0 else
 */
int	is_a_player(t_parse_map *to_copy, t_map *map, int i, int j)
{
	if (to_copy->blocks[j] == 'N' || to_copy->blocks[j] == 'S'
		|| to_copy->blocks[j] == 'E' || to_copy->blocks[j] == 'W')
	{
		map->blocks[i][j].type = FLOOR;
		map->player.x = j + 0.5;
		map->player.y = i + 0.5;
		if (to_copy->blocks[j] == 'N')
			map->player.dir = NORTH;
		else if (to_copy->blocks[j] == 'E')
			map->player.dir = EAST;
		else if (to_copy->blocks[j] == 'S')
			map->player.dir = SOUTH;
		else if (to_copy->blocks[j] == 'W')
			map->player.dir = WEST;
		return (1);
	}
	return (0);
}

/**
 * @brief Fill the map with void from last block to max_size
 * @param map the map
 * @param i the i index
 * @param j the j index
 * @param max_size the max size
 * @return void
 */
void	fill_with_void(t_map *map, int i, int j, int max_size)
{
	while (j < max_size)
	{
		map->blocks[i][j].type = VOID;
		map->blocks[i][j].status = 0;
		j++;
	}
}

/**
 * @brief Loop through the blocks and fill the map
 * @param to_copy the parse map
 * @param map the map
 * @param i the i index
 * @param player_nb the player number
 * @return int 1 if error, 0 if success
 */
int	blocks_loop(t_parse_map *to_copy, t_map **map, int i, int *player_nb)
{
	int	j;
	int	max_size;

	j = -1;
	while (to_copy->blocks[++j])
	{
		if (is_wall_floor_door(to_copy, (*map), i, j))
			continue ;
		if (is_a_player(to_copy, (*map), i, j))
		{
			(*player_nb)++;
			continue ;
		}
		if (to_copy->blocks[j] == '\n')
			break ;
		if (to_copy->blocks[j])
		{
			ft_fprintf(STDERR_FILENO,
				"Error: invalid character in map : [%c]\n", to_copy->blocks[j]);
			return (1);
		}
	}
	max_size = parse_map_max_size(to_copy);
	fill_with_void((*map), i, j, max_size);
	return (0);
}

/**
 * @brief Copy the tab to the map
 * @param to_copy the parse map
 * @param map the map
 * @param images the images
 * @return int 1 if error, 0 if success
 */
int	copy_tab_to_map(t_parse_map *to_copy, t_map *map, char ***images)
{
	int	i;
	int	player_nb;

	i = 0;
	player_nb = 0;
	if (checking_firsts_map_lines(&to_copy, images))
		return (1);
	while (ft_strncmp(to_copy->blocks, "\n", 1) == 0)
		to_copy = to_copy->next;
	while (to_copy)
	{
		if (blocks_loop(to_copy, &map, i, &player_nb) == 1)
			return (1);
		i++;
		to_copy = to_copy->next;
	}
	if (player_nb != 1)
	{
		ft_fprintf(STDERR_FILENO, "Error: no player or too many players\n");
		return (1);
	}
	return (0);
}
