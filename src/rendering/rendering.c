#include "cube.h"

static void	paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos)
{
	int i;
	int j;
	int color;
	int alpha;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			color = *(int *)(image->img_data + (i * image->bpp / 8) + (j * image->size_line));
			alpha = (color >> 24) & 0xFF;

			if (pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y < 0 || pos.y >= SCREEN_HEIGHT)
				return ;
			if (alpha == 0)
				*(int *)(win->img_data + ((int)pos.x + i) * win->bpp / 8 + ((int)pos.y + j) * win->size_line) = color;
			j++;
		}
		i++;
	}
}
static void process_ray(t_image *img, t_map *map, t_ray *ray, int ray_index)
{
	t_image	*texture;
	int		height;
	int		width;
	int		x;
	int		y;
	int		texture_x;
	double	corrected_distance;

	double add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	if (ray->angle > 360)
        ray->angle -= 360;
	else if(ray->angle < 0)
		ray->angle += 360;

	if (ray->type == DOOR)
		texture = map->textures->door;
	else if (ray->side == 1)
	{
		if (ray->angle > 0 && ray->angle < 180)
			texture = map->textures->wall_north;
		else
			texture = map->textures->wall_south;
	}
	else
	{
		if (ray->angle > 90 && ray->angle < 270)
			texture = map->textures->wall_east;
		else
			texture = map->textures->wall_west;
	}

	double ray_angle = add_angle * M_PI / 180.0;
	corrected_distance = ray->distance * cos(ray_angle);

	if (corrected_distance < 0.1)
		corrected_distance = 0.1;

	height = (int)(SCREEN_HEIGHT / corrected_distance);
	width = fmax(1, SCREEN_WIDTH / RAYS_COUNT);

	texture_x = (int)(ray->x_axis * texture->width) % texture->width;

	x = ray_index * width;
	y = (SCREEN_HEIGHT - height) / 2;

	for (int screen_y = 0; screen_y < height; screen_y++) {
		int texture_y = (screen_y * texture->height) / height;
		int pixel_color = get_pixel_color(texture, ft_vector2(texture_x, texture_y));
		set_pixel_color(img, ft_vector2(x, y + screen_y), pixel_color);
	}

	draw_rectangle(img, ft_vector2(x, 0), width, y, map->textures->ceiling.r);

	draw_rectangle(img, ft_vector2(x, y + height), width, SCREEN_HEIGHT - (y + height), map->textures->floor.g);
}

static void render_game(t_image *img, t_map *map)
{
	t_ray	*ray;
	int 	i;

	ray = map->rays;
	i = 0;
	while (ray)
	{
		process_ray(img, map, ray, i);
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
	t_image		*minimap;
	t_image		*render;
	t_vector2	hand_pos;

	give_all_rays(map);
	minimap = draw_minimap(map, win->mlx_ptr);
	if (!minimap)
		return;
	render = ft_init_image(win->mlx_ptr, SCREEN_WIDTH, SCREEN_HEIGHT);
	render_game(render, map);
	paste_image_on_screen(win, render, ft_vector2(0, 0));
	mlx_destroy_image(win->mlx_ptr, render->img_ptr);
	free(render);
	paste_image_on_screen(win, minimap, ft_vector2(0, 0));
	if (map->player.hand_animation_direction)
		map->player.hand_animation_pos += 1;
	else
		map->player.hand_animation_pos -= 1;
	if (map->player.hand_animation_pos >= 100 || map->player.hand_animation_pos <= -100)
		map->player.hand_animation_direction = !map->player.hand_animation_direction;
	hand_pos = ft_vector2(SCREEN_WIDTH - map->textures->right_hand->width - 10, SCREEN_HEIGHT - map->textures->right_hand->height + 10 + map->player.hand_animation_pos / 10);
	paste_image_on_screen(win, map->textures->right_hand, hand_pos);

	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_destroy_image(win->mlx_ptr, minimap->img_ptr);
	free(minimap);
}
