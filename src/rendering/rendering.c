#include "cube.h"

static void texture_selection(t_map *map, t_ray *ray, t_image **texture)
{
	if (ray->angle > 360)
        ray->angle -= 360;
	else if(ray->angle < 0)
		ray->angle += 360;

	if (ray->type == DOOR)
		(*texture) = map->textures->door;
	else if (ray->side == 1)
	{
		if (ray->angle > 0 && ray->angle < 180)
			(*texture) = map->textures->wall_north;
		else
			(*texture) = map->textures->wall_south;
	}
	else
	{
		if (ray->angle > 90 && ray->angle < 270)
			(*texture) = map->textures->wall_east;
		else
			(*texture) = map->textures->wall_west;
	}
}

static void process_ray(t_win *win, t_map *map, t_ray *ray, int ray_index)
{
	t_image	*texture;
	int		height;
	int		width;
	int		texture_x;
	double	corrected_distance;
	t_vector2 pos;

	double add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	texture_selection(map, ray, &texture);
	double ray_angle = add_angle * M_PI / 180.0;
	corrected_distance = ray->distance * cos(ray_angle);
	if (corrected_distance < 0.1)
		corrected_distance = 0.1;
	height = (int)(SCREEN_HEIGHT / corrected_distance);
	width = fmax(1, SCREEN_WIDTH / RAYS_COUNT);
	texture_x = (int)(ray->x_axis * texture->width) % texture->width;
	pos.x = ray_index * width;
	pos.y = (SCREEN_HEIGHT - height) / 2;
	x = ray_index * width;
	y = (SCREEN_HEIGHT - height) / 2;
	double	texture_step = (double)texture->height / height;
	double	texture_pos = 0.0;
	int		screen_y = 0;
	int i = 0;
	while (screen_y < height)
	{
		i++;
		if (ray->distance < 0.5 && i % 2)
			continue;
		int texture_y = (int)texture_pos % texture->height;
		texture_pos += texture_step;
		int pixel_color = get_pixel_color(texture, ft_vector2(texture_x, texture_y));
		set_pixel_color(win, ft_vector2(pos.x, pos.y + screen_y), pixel_color);
		screen_y++;
	}
	draw_rectangle(win, ft_vector2(pos.x, 0), width, pos.y, map->textures->ceiling.r);
	draw_rectangle(win, ft_vector2(pos.x, pos.y + height), width, SCREEN_HEIGHT - (pos.y + height), map->textures->floor.g);
}

static void render_game(t_win *win, t_map *map)
{
	t_ray	*ray;
	int 	i;

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
	if (map->player.hand_animation_pos >= 100 || map->player.hand_animation_pos <= -100)
		map->player.hand_animation_direction = !map->player.hand_animation_direction;
	hand_pos = ft_vector2(SCREEN_WIDTH - map->textures->right_hand->width - 10, SCREEN_HEIGHT - map->textures->right_hand->height + 10 + map->player.hand_animation_pos / 10);
	paste_image_on_screen(win, map->textures->right_hand, hand_pos);

	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}
