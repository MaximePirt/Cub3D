/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug_print.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:48:23 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/01 00:48:44 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	print_enum_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->blocks[i][j].type == VOID)
				ft_printf("V");
			else if (map->blocks[i][j].type == FLOOR)
				ft_printf("0");
			else if (map->blocks[i][j].type == WALL)
				ft_printf("1");
			else if (map->blocks[i][j].type == DOOR)
				ft_printf("D");
			else if (map->blocks[i][j].type == FILL)
				ft_printf("F");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

/**
 * @brief Print the parsed map
 *	TODO: Delet, this function is only for debug
 */
void	print_parse_map(t_parse_map *map)
{
	t_parse_map	*tmp;

	tmp = map;
	ft_printf("\n\n////////////DEBUG MAP/////////////\n");
	while (tmp)
	{
		ft_printf("%s", tmp->blocks);
		tmp = tmp->next;
	}
	tmp = map;
	ft_printf("\n\n////////////DEBUG  LEN/////////////\n");
	while (tmp)
	{
		ft_printf("len [%d]\n", tmp->blocks_len);
		tmp = tmp->next;
	}
	return ;
}
