/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:40:32 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/27 00:59:03 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

/**
 * @brief Check the name of the file
 * @param file the file
 * @return int 1 if success, 0 if error
 */
static int	load_textures(t_map *map, t_win *win, char **images)
{
	int	i;

	if (load_texture(map->textures->wall_north, images[0], win->mlx_ptr) == 1)
		return (1);
	if (load_texture(map->textures->wall_south, images[1], win->mlx_ptr) == 1)
		return (1);
	if (load_texture(map->textures->wall_east, images[2], win->mlx_ptr) == 1)
		return (1);
	if (load_texture(map->textures->wall_west, images[3], win->mlx_ptr) == 1)
		return (1);
	if (fill_rgb_texture(&map->textures->floor, images[4]) == 1)
		return (1);
	if (fill_rgb_texture(&map->textures->ceiling, images[5]) == 1)
		return (1);
	if (load_texture(map->textures->door, images[6], win->mlx_ptr) == 1)
		return (1);
	if (load_texture(map->textures->right_hand, images[7], win->mlx_ptr) == 1)
		return (1);
	i = 0;
	while (i < 8)
		free(images[i++]);
	free(images);
	return (0);
}

static int	init_game(int argc, char **argv, t_map **map, char ***images)
{
	int	i;

	*map = NULL;
	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Error: please provide a map file\n");
		return (1);
	}
	if (check_name(argv[1]))
	{
		ft_fprintf(STDERR_FILENO,
			"Error : filename doesn't respect the subject\n");
		return (1);
	}
	*images = ft_calloc(sizeof(char *), 9);
	if (check_map(map, argv[1], images) == 1)
	{
		i = 0;
		while (i < 8)
			free((*images)[i++]);
		free(*images);
		ft_fprintf(STDERR_FILENO, "Error: invalid map\n");
		return (1);
	}
	return (0);
}

static int	ft_free_error(t_map *map, t_win *win)
{
	if (map)
	{
		ft_free_map(map->blocks, map->size_y);
		ft_free_rays(map->rays);
		if (win)
			ft_free_textures(win, map->textures);
		free(map->minimap->image);
		free(map->minimap);
		free(map);
	}
	if (win)
	{
		mlx_destroy_image(win->mlx_ptr, win->img_ptr);
		mlx_clear_window(win->mlx_ptr, win->win_ptr);
		mlx_destroy_window(win->mlx_ptr, win->win_ptr);
		mlx_destroy_display(win->mlx_ptr);
		free(win->mlx_ptr);
		free(win);
	}
	exit(0);
}

static void	launch_game(t_win *win, t_map *map, t_key_params *params)
{
	params->win = win;
	params->map = map;
	ft_init_keymap(params);
	mlx_loop_hook(win->mlx_ptr, game_loop, params);
	mlx_loop(win->mlx_ptr);
}

int	main(int argc, char **argv)
{
	t_win			*win;
	t_map			*map;
	char			**images;
	t_key_params	*params;

	win = ft_init_window();
	if (init_game(argc, argv, &map, &images) == 1)
		ft_free_error(map, win);
	if (load_textures(map, win, images))
	{
		free_images(images);
		ft_free_error(map, win);
	}
	map->minimap->image = ft_init_image(win->mlx_ptr, MINIMAP_RENDER_DISTANCE
			* map->minimap->zoom, MINIMAP_RENDER_DISTANCE * map->minimap->zoom);
	if (map->minimap->image == NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error: failed to init minimap\n");
		return (1);
	}
	params = (t_key_params *)malloc(sizeof(t_key_params));
	if (params == NULL)
		exit(0);
	launch_game(win, map, params);
	return (0);
}
