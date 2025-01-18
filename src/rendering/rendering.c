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

static void process_ray(t_win *win, t_map *map, t_ray *ray, int ray_index)
{
	t_image	*texture;
	int		screen_height;
	int		screen_width;
	int		height;
	int		width;
	double	angle;
	int		x;
	int		y;
	int		texture_x;

	screen_height = SCREEN_HEIGHT;
	screen_width = SCREEN_WIDTH;

	double add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	angle = fmod(map->player.dir + add_angle + 360, 360);

	if (angle >= 0 && angle < 90)
		texture = map->textures->wall_north;
	else if (angle >= 90 && angle < 180)
		texture = map->textures->wall_east;
	else if (angle >= 180 && angle < 270)
		texture = map->textures->wall_south;
	else
		texture = map->textures->wall_west;

	height = screen_height / ray->distance;
	width = fmin(1, screen_width / RAYS_COUNT);

	texture_x = (int)((ray->x_axis - floor(ray->x_axis)) * texture->width);

	x = ray_index * width;
	y = (screen_height - height) / 2;

	// Débogage des valeurs

	// Copier les pixels de la texture vers l'écran
	copy_vertical_pixels(win, texture, ft_vector2(x, y), height, width, texture_x);

	// Dessiner le plafond
	//draw_rectangle(win, ft_vector2(x, 0), width, y, map->textures->ceiling.r);

	// Dessiner le sol
	//draw_rectangle(win, ft_vector2(x, y + height), width, screen_height - (y + height), map->textures->floor.g);
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
	t_image	*minimap;
	t_vector2 hand_pos;

	give_all_rays(map);
	minimap = draw_minimap(map, win->mlx_ptr);
	if (!minimap)
		return;
	render_game(win, map);
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
