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

static	int main_loop(t_key_params *params)
{
	int	x;
	int	y;

	refresh(params->win, params->map);
	if (params->map->mouse_lock)
	{
		mlx_mouse_get_pos(params->win->mlx_ptr, params->win->win_ptr, &x, &y);
		mlx_mouse_move(params->win->mlx_ptr, params->win->win_ptr, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
		if (x > SCREEN_WIDTH / 2)
			player_look_right(params->map);
		else if (x < SCREEN_WIDTH / 2)
			player_look_left(params->map);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_win	*win;
	t_map	*map;
	char	**images;

	if (argc != 2)
	{
		ft_fprintf(STDERR_FILENO, "Error: please provide a map file\n");
		return (1);
	}
	if (check_name(argv[1]))
	{
		ft_fprintf(STDERR_FILENO, "Error : filename doesn't respect the subject\n");
		return (1);	
	}
	map = NULL;
	images = ft_calloc(sizeof(char *), 8);
	if (check_map(&map, argv[1], &images) == 1)
	{
		ft_tabfree(images);
		ft_fprintf(STDERR_FILENO, "Error: invalid map\n");
		return (1);
	}
  
	win = ft_init_window();
    //TODO: RETURN (1) IS TEMPORARY, NEED TO WORK ON THE EXIT WAY
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
		return (1); //TODO: Remove, it's the door
	if (load_texture(map->textures->right_hand, images[7], win->mlx_ptr) == 1)
		return (1);

	ft_tabfree(images);
	//	//TODO: render map
	ft_init_keymap(win, map);

	t_key_params	*params;

	params = (t_key_params *)malloc(sizeof(t_key_params));
	if (params == NULL)
	{
		ft_fprintf(STDERR_FILENO, "malloc error in ft_init_keymap\n");
		exit(0);
	}
	params->win = win;
	params->map = map;
	mlx_loop_hook(win->mlx_ptr, main_loop, params);
	mlx_loop(win->mlx_ptr);
	return (0);
}