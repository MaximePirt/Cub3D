#include "cube.h"

t_block	*ft_init_block(int x, int y, int z)
{
	t_block	*block;

	block = (t_block *)malloc(sizeof(t_block));
	if (block == NULL)
		return (NULL);
	block->type = VOID;
	block->status = 0;
	return (block);
}

t_block	**ft_alloc_map(int size_x, int size_y)
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
	}
	return (map);
}

t_map	*ft_init_map(int size_x, int size_y)
{
	t_map	*map;

	map = (t_map *)malloc(sizeof(t_map));
	if (map == NULL)
		return (NULL);
	map->map = ft_alloc_map(size_x, size_y);
	if (map->map == NULL)
	{
		free(map);
		return (NULL);
	}
	map->size_x = size_x;
	map->size_y = size_y;
	return (map);
}
