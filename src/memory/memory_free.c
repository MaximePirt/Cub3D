#include "cube.h"

static void	*ft_free_map(t_block **blocks, int size_y)
{
	int	i;

	i = -1;
	while (++i < size_y)
		free(blocks[i]);
	free(blocks);
	return (NULL);
}

static void *ft_free_textures(t_textures *textures)
{
	free(textures->wall_north);
	free(textures->wall_south);
	free(textures->wall_east);
	free(textures->wall_west);
	free(textures->door);
	free(textures);
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

	ft_free_map(params->map->blocks, params->map->size_y);
	ft_free_textures(params->map->textures);
	free(params->map);
	free(params);
	exit(0);
}
