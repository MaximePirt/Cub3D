/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 00:40:32 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/10 21:47:47 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	fill_map_test(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (i == 0 || i == map->size_y - 1 || j == 0 || j == map->size_x - 1)
				map->blocks[i][j].type = WALL;
			else
				map->blocks[i][j].type = FLOOR;
			j++;
		}
		i++;
	}
	map->player.x = map->size_x / 2;
	map->player.y = map->size_y / 2;
	map->player.dir = 0;
}

int	main(int argc, char **argv)
{
	t_win	*win;
	t_map	*map;
	char	**images;

	if (argc != 2)
	{
		ft_printf("Error: please provide a map file\n");
		return (1);
	}
	if (check_name(argv[1]))
	{
		ft_fprintf(2, "Error : filename doesn't respect the subject\n");
		return (1);	
	}
	map = NULL;
	images = ft_calloc(sizeof(char *), 8);
	if (check_map(&map, argv[1], &images) == 1)
	{
		ft_tabfree(images);
		ft_printf("Error: invalid map\n");
		return (1);
	}
	win = ft_init_window();
    //TODO: RETURN (1) IS TEMPORARY, NEED TO WORK ON THE EXIT WAY
	// if (load_texture(map->textures->wall_north, images[0], win->mlx_ptr) == 1)
	// 	return (1);
	// if (load_texture(map->textures->wall_south, images[1], win->mlx_ptr) == 1)
	// 	return (1);
	// if (load_texture(map->textures->wall_east, images[2], win->mlx_ptr) == 1)
	// 	return (1);
	// if (load_texture(map->textures->wall_west, images[3], win->mlx_ptr) == 1)
	// 	return (1);
	// if (fill_rgb_texture(&map->textures->floor, images[4]) == 1)
	// 	return (1);
	// if (fill_rgb_texture(&map->textures->ceiling, images[5]) == 1)
	// 	return (1);
	// if (load_texture(map->textures->door, images[6], win->mlx_ptr) == 1)
	// 	return (1); //TODO: Remove, it's the door
	//	//TODO: render map
		// refresh(win, map);
		// ft_init_keymap(win, map);
		// mlx_loop(win->mlx_ptr);
	ft_tabfree(images);
	ft_free_map(map->blocks, map->size_y);
    ft_free_textures(win, map->textures);
    free(map);
	return (0);
}