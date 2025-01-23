/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minimap.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/01 06:13:17 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static int	find_map_color(t_map *map, int i, int j)
{
	if (i >= 0 && i < map->size_x && j >= 0 && j < map->size_y)
	{
		if (map->blocks[j][i].type == WALL)
			return (HEX_BLACK);
		if (map->blocks[j][i].type == DOOR)
			return (HEX_CYAN);
		return (HEX_WHITE);
	}
	return (HEX_WHITE);
}

/**
 * @brief Draw the player on the minimap
 * @param img the image
 * @param zoom the zoom
 */
static void	draw_minimap_player(t_image *img, int zoom)
{
	int	xy;

	xy = (MINIMAP_RENDER_DISTANCE / 2) * zoom;
	draw_circle(img,
		ft_vector2(xy, xy),
		zoom / 4,
		HEX_RED);
}

/**
 * @brief Draw the minimap part 2 (thx norminette...)
 * @param start the start
 * @param end the end
 * @param map the map
 */
static void	draw_minimap_2(t_vector2 start, t_vector2 end, t_map *map)
{
	t_vector2	offset;
	int			i;
	int			j;

	j = start.y;
	while (j < end.y)
	{
		i = start.x;
		while (i < end.x)
		{
			offset = ft_vector2((i - start.x) * map->minimap->zoom,
					(j - start.y) * map->minimap->zoom);
			draw_square(map->minimap->image,
				offset, map->minimap->zoom, find_map_color(map, i, j));
			i++;
		}
		j++;
	}
}

/**
 * @brief Draw the minimap
 * @param map the map
 */
void	draw_minimap(t_map *map)
{
	t_vector2	start;
	t_vector2	end;

	start = ft_vector2(map->player.x - MINIMAP_RENDER_DISTANCE / 2,
			map->player.y - MINIMAP_RENDER_DISTANCE / 2);
	end = ft_vector2(start.x + MINIMAP_RENDER_DISTANCE,
			start.y + MINIMAP_RENDER_DISTANCE);
	draw_minimap_2(start, end, map);
	draw_minimap_player(map->minimap->image, map->minimap->zoom);
}
