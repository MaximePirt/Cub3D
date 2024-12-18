/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   floodfill.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:35:55 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/11 17:57:18 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Manage the stack for the flood fill algorithm
 * 		by adding the position to the stack
 * @param stack the stack
 * @param x the x position
 * @param y the y position
 * @param pos the position
 * @return void
 */
static void	manage_stack(t_stack *stack, int x, int y, int *pos)
{
	(*pos)++;
	stack[*pos].x = x - 1;
	stack[*pos].y = y;
	(*pos)++;
	stack[*pos].x = x + 1;
	stack[*pos].y = y;
	(*pos)++;
	stack[*pos].x = x;
	stack[*pos].y = y - 1;
	(*pos)++;
	stack[*pos].x = x;
	stack[*pos].y = y + 1;
	return ;
}

/**
 * @brief Manage the blocks for the flood fill algorithm
 * 		by checking if the block is valid
 * @param x the x position
 * @param y the y position
 * @param map the map
 * @param stack the stack
 * @return int : 0 if the block is valid, 1 if the block is next to a void,
 *	2 if the block is invalid
 */
static int	floodfill_blocks_management(int x, int y, t_map *map,
		t_stack *stack)
{
	if (x >= map->size_y || y >= map->size_x || !map->blocks[x][y].type
		|| map->blocks[x][y].type == WALL || map->blocks[x][y].type == FILL)
		return (2);
	if (!map->blocks[x - 1] || !map->blocks[x][y
		- 1].type || (map->blocks[x+1] && map->blocks[x + 1][y].type == VOID)
		||  map->blocks[x - 1][y].type == VOID
		|| map->blocks[x][y + 1].type == VOID || map->blocks[x][y
		- 1].type == VOID)
	{
		ft_fprintf(STDERR_FILENO, "Error: map is not closed here %d %d\n", x, y);
		free(stack);
		return (1);
	}
	return (0);
}

/**
 * @brief Flood fill algorithm to fill the map in iterative version
 * @param map the map
 * @param x the x position
 * @param y the y position
 * @return t_map*
 *
 */
int	flood_fill(t_map *map, int x, int y)
{
	t_stack	*stack;
	int		pos;
	int		block_management;

	if (x <= 0 || y <= 0 || x >= map->size_y || y >= map->size_x)
	    return (1);
	stack = malloc(sizeof(t_stack) * map->size_x * map->size_y);
	if (!stack)
		return (1);
	pos = 0;
	stack[pos].x = x;
	stack[pos].y = y;
	pos++;
	while (pos-- > 0)
	{
		x = stack[pos].x;
		y = stack[pos].y;
		block_management = floodfill_blocks_management(x, y, map, stack);
		if (block_management == 1)
			return (1);
		if (block_management == 2)
			continue ;
		map->blocks[x][y].type = FILL;
		manage_stack(stack, x, y, &pos);
	}
	free(stack);
	return (0);
}
