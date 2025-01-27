/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_alloc.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:39:47 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static t_block	**ft_alloc_map(int size_x, int size_y)
{
	t_block	**map;
	int		i;

	map = (t_block **)malloc(sizeof(t_block *) * (size_y));
	if (map == NULL)
		return (NULL);
	i = -1;
	while (++i < size_y)
	{
		map[i] = (t_block *)malloc(sizeof(t_block) * (size_x));
		if (map[i] == NULL)
		{
			while (--i >= 0)
				free(map[i]);
			free(map);
			return (NULL);
		}
		map[i] = ft_memset(map[i], 0, sizeof(t_block) * size_x);
	}
	return (map);
}

static t_player	ft_init_player(void)
{
	t_player	player;

	player.x = 0;
	player.y = 0;
	player.dir = 0;
	player.texture = NULL;
	player.hand_animation_pos = 0;
	player.hand_animation_direction = 0;
	return (player);
}

static t_minimap	*ft_init_minimap(void)
{
	t_minimap	*minimap;

	minimap = (t_minimap *)malloc(sizeof(t_minimap));
	if (minimap == NULL)
		return (NULL);
	minimap->zoom = SCREEN_WIDTH / MINIMAP_RENDER_DISTANCE / 5;
	minimap->image = NULL;
	return (minimap);
}

t_map	*ft_init_map(int size_x, int size_y)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->blocks = ft_alloc_map(size_x, size_y);
	if (map->blocks == NULL)
	{
		free(map);
		return (NULL);
	}
	map->player = ft_init_player();
	map->textures = ft_init_textures();
	if (map->textures == NULL)
	{
		free(map->blocks);
		free(map);
		return (NULL);
	}
	map->size_x = size_x;
	map->size_y = size_y;
	map->rays = ft_init_rays();
	map->minimap = ft_init_minimap();
	map->mouse_lock = 0;
	return (map);
}
