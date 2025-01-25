/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   memory_free.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:34:32 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	ft_free_texture(t_win *win, t_image *image)
{
	if (image->path)
		free(image->path);
	if (image->img_ptr)
		mlx_destroy_image(win->mlx_ptr, image->img_ptr);
	free(image);
}

void	ft_free_textures(t_win *win, t_textures *textures)
{
	ft_free_texture(win, textures->wall_north);
	ft_free_texture(win, textures->wall_south);
	ft_free_texture(win, textures->wall_east);
	ft_free_texture(win, textures->wall_west);
	ft_free_texture(win, textures->right_hand);
	free(textures);
}

void	*ft_free_map(t_block **blocks, int size_y)
{
	int	i;

	i = -1;
	while (++i < size_y)
		free(blocks[i]);
	free(blocks);
	return (NULL);
}

void	free_parse_map(t_parse_map *map)
{
	t_parse_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->blocks);
		free(tmp);
	}
}

int	ft_free_program(t_key_params *params)
{
	ft_free_map(params->map->blocks, params->map->size_y);
	ft_free_rays(params->map->rays);
	ft_free_textures(params->win, params->map->textures);
	mlx_destroy_image(params->win->mlx_ptr,
		params->map->minimap->image->img_ptr);
	free(params->map->minimap->image);
	free(params->map->minimap);
	mlx_destroy_image(params->win->mlx_ptr, params->win->img_ptr);
	mlx_clear_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_window(params->win->mlx_ptr, params->win->win_ptr);
	mlx_destroy_display(params->win->mlx_ptr);
	free(params->win->mlx_ptr);
	free(params->win);
	free(params->map);
	free(params);
	exit(0);
}
