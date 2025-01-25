/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rendering_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:50:59 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	texture_selection(t_map *map, t_ray *ray, t_image **texture)
{
	if (ray->angle > 360)
		ray->angle -= 360;
	else if (ray->angle < 0)
		ray->angle += 360;
	if (ray->type == DOOR)
		*texture = map->textures->door;
	else if (ray->side == 1)
	{
		if (ray->angle > 0 && ray->angle < 180)
			*texture = map->textures->wall_north;
		else
			*texture = map->textures->wall_south;
	}
	else
	{
		if (ray->angle > 90 && ray->angle < 270)
			*texture = map->textures->wall_east;
		else
			*texture = map->textures->wall_west;
	}
}

static void	process_loop(t_image *texture, t_ray *ray, t_win *win,
		t_calcul_process calc)
{
	t_vector2	texture_xy;
	double		texture_pos;
	double		texture_step;
	int			i;
	int			screen_y;

	i = 0;
	screen_y = 0;
	texture_pos = 0.0;
	texture_xy.x = (int)(ray->x_axis * texture->width) % texture->width;
	if ((ray->side == 1 && ray->angle >= 0 && ray->angle < 180)
		|| (ray->side == 0 && (ray->angle >= 90 && ray->angle < 270)))
		texture_xy.x = texture->width - 1 - texture_xy.x;
	texture_step = (double)texture->height / calc.height;
	while (screen_y < calc.height)
	{
		i++;
		if (ray->distance < 0.5 && i % 2)
			continue ;
		texture_xy.y = (int)texture_pos % texture->height;
		texture_pos += texture_step;
		set_pixel_color(win, ft_vector2(calc.pos.x, calc.pos.y + screen_y),
			get_pixel_color(texture, ft_vector2(texture_xy.x, texture_xy.y)));
		screen_y++;
	}
}

static void	process_ray(t_win *win, t_map *map, t_ray *ray, int ray_index)
{
	t_image				*texture;
	t_calcul_process	calc;
	double				corrected_distance;

	calc.add_angle = ray_index * (FOV / (double)RAYS_COUNT) - FOV / 2;
	texture_selection(map, ray, &texture);
	calc.ray_angle = calc.add_angle * M_PI / 180.0;
	corrected_distance = ray->distance * cos(calc.ray_angle);
	if (corrected_distance < 0.1)
		corrected_distance = 0.1;
	calc.height = (int)(SCREEN_HEIGHT / corrected_distance);
	calc.width = fmax(1, SCREEN_WIDTH / RAYS_COUNT);
	calc.pos = ft_vector2(ray_index * calc.width, (SCREEN_HEIGHT - calc.height)
			/ 2);
	process_loop(texture, ray, win, calc);
	draw_rectangle(win, ft_vector2(calc.pos.x, 0), ft_vector2(calc.width,
			calc.pos.y), map->textures->ceiling.r);
	draw_rectangle(win, ft_vector2(calc.pos.x, calc.pos.y + calc.height),
		ft_vector2(calc.width, SCREEN_HEIGHT - (calc.pos.y + calc.height)),
		map->textures->floor.g);
}

static void	render_game(t_win *win, t_map *map)
{
	t_ray	*ray;
	int		i;

	ray = map->rays;
	i = 0;
	while (ray)
	{
		process_ray(win, map, ray, i);
		ray = ray->next;
		i++;
	}
}

/**
 * @brief Refresh the screen with the new image.
 *
 * @param t_win *win The window to refresh.
 * @param t_map *map The map to render.
 */
void	refresh(t_win *win, t_map *map)
{
	t_vector2	hand_pos;

	give_all_rays(map);
	render_game(win, map);
	ft_fill_image(map->minimap->image, HEX_WHITE);
	draw_minimap(map);
	paste_image_on_screen(win, map->minimap->image, ft_vector2(0, 0));
	if (map->player.hand_animation_direction)
		map->player.hand_animation_pos += 1;
	else
		map->player.hand_animation_pos -= 1;
	if (map->player.hand_animation_pos >= 100
		|| map->player.hand_animation_pos <= -100)
		map->player.hand_animation_direction \
		= !map->player.hand_animation_direction;
	hand_pos = ft_vector2(SCREEN_WIDTH - map->textures->right_hand->width - 10,
			SCREEN_HEIGHT - map->textures->right_hand->height + 10
			+ map->player.hand_animation_pos / 10);
	paste_image_on_screen(win, map->textures->right_hand, hand_pos);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
