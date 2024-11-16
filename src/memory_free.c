#include "cube.h"

static void	*ft_free_map(t_map *map)
{
	int	i;

	i = 0;
	while (i < map->size_z)
	{
		free(map->map_vector3[i]);
		i++;
	}

	free(map);
	return (NULL);
}

int	ft_free_program(t_key_params *params)
{
	mlx_destroy_image(params->win->mlx_ptr, params->win->img_ptr);
	mlx_clear_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_display(params->win->mlx_ptr);
	free(params->win->mlx_ptr);
	free(params->win);

	ft_free_map(params->map);
	free(params);
	exit(0);
}
