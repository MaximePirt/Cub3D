#include "cube.h"

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

static void	draw_walls(t_cache cache, t_ray *ray, t_win *win, t_map *map)
{
	int		texture_y;
	double	texture_pos;
	int		screen_y;
	int		i;

	texture_pos = 0.0;
	screen_y = 0;
	i = 0;
	while (screen_y < cache.height)
	{
		i++;
		if (ray->distance < 0.5 && i % 2)
			continue ;
		texture_y = (int)texture_pos % cache.texture->height;
		texture_pos += cache.texture_step;
		set_pixel_color(win, ft_vector2(cache.pos.x, cache.pos.y + screen_y),
			get_pixel_color(cache.texture,
				ft_vector2(cache.texture_x, texture_y)));
		screen_y++;
	}
	draw_rectangle(win, ft_vector2(cache.pos.x, 0),
		ft_vector2(cache.width, cache.pos.y), map->textures->ceiling.r);
	draw_rectangle(win, ft_vector2(cache.pos.x, cache.pos.y + cache.height),
		ft_vector2(cache.width, SCREEN_HEIGHT - (cache.pos.y + cache.height)),
		map->textures->floor.g);
}

static void	process_ray(t_win *win, t_map *map, t_ray *ray, int ray_index)
{
	t_cache	cache;

	cache.add_angle = ray_index * (FOV / (double)RAYS_COUNT) - FOV / 2;
	texture_selection(map, ray, &cache.texture);
	cache.ray_angle = cache.add_angle * M_PI / 180.0;
	cache.corrected_distance = ray->distance * cos(cache.ray_angle);
	if (cache.corrected_distance < 0.1)
		cache.corrected_distance = 0.1;
	cache.height = (int)(SCREEN_HEIGHT / cache.corrected_distance);
	cache.width = fmax(1, SCREEN_WIDTH / RAYS_COUNT);
	cache.texture_x = (int)(ray->x_axis * cache.texture->width)
		% cache.texture->width;
	cache.pos.x = ray_index * cache.width;
	cache.pos.y = (SCREEN_HEIGHT - cache.height) / 2;
	cache.texture_step = (double)cache.texture->height / cache.height;
	draw_walls(cache, ray, win, map);
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
	draw_minimap(map);
	paste_image_on_screen(win, map->minimap->image, ft_vector2(0, 0));
	if (map->player.hand_animation_direction)
		map->player.hand_animation_pos += 1;
	else
		map->player.hand_animation_pos -= 1;
	if (map->player.hand_animation_pos >= 100
		|| map->player.hand_animation_pos <= -100)
		map->player.hand_animation_direction
			= !map->player.hand_animation_direction;
	hand_pos = ft_vector2(SCREEN_WIDTH - map->textures->right_hand->width - 10,
			SCREEN_HEIGHT - map->textures->right_hand->height + 10
			+ map->player.hand_animation_pos / 10);
	paste_image_on_screen(win, map->textures->right_hand, hand_pos);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
