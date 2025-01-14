#include "cube.h"

static void	paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos)
{
	int i;
	int j;
	int color;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			color = *(int *)(image->img_data + (i * image->bpp / 8) + (j * image->size_line));

			if (pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y < 0 || pos.y >= SCREEN_HEIGHT)
				return ;
			*(int *)(win->img_data + ((int)pos.x + i) * win->bpp / 8 + ((int)pos.y + j) * win->size_line) = color;
			j++;
		}
		i++;
	}
}

static void process_ray(t_win *win, t_map *map, double distance, int ray_index)
{
	t_image	*texture;
	int		height;
	int 	width;
	int 	direction;
	int		x;
	int		y;
	//decrese distance by a random value between 0 and 3
	distance -= (rand() % 3);
	height = (int)(SCREEN_HEIGHT / distance);
	//ray witdh corresponds to: SCREEN_WIDTH / RAYS_COUNT
	width = SCREEN_WIDTH / RAYS_COUNT;
	direction = map->player.dir + (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	//x corresponds to the direction of the ray on the texture
	x = (ray_index - 1) * width;
	y = (SCREEN_HEIGHT - height) / 2;
	//get correct texture depending on the direction
	if (direction >= 0 && direction < 90)
		texture = map->textures->wall_north;
	else if (direction >= 90 && direction < 180)
		texture = map->textures->wall_east;
	else if (direction >= 180 && direction < 270)
		texture = map->textures->wall_south;
	else
		texture = map->textures->wall_west;
	copy_vertical_pixels(win, texture, ft_vector2(x, y), height, width);
	draw_rectangle(win, ft_vector2(x, 0), width, (SCREEN_WIDTH - height) / 2, map->textures->ceiling.r);
	draw_rectangle(win, ft_vector2(x, (SCREEN_HEIGHT + height) / 2), width, (SCREEN_WIDTH - height) / 2, map->textures->floor.g);
}

static void render_game(t_win *win, t_map *map)
{
	t_ray	*ray;
	int 	i;

	ray = map->rays;
	i = 1;
	while (ray)
	{
		process_ray(win, map, ray->distance, i);
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

 	give_all_rays(map);
	minimap = draw_minimap(map, win->mlx_ptr);
	if (!minimap)
		return;
	render_game(win, map);
	paste_image_on_screen(win, minimap, ft_vector2(0, 0));
	//paste_image_on_screen(win, map->textures->right_hand, ft_vector2(SCREEN_WIDTH - map->textures->right_hand->width, SCREEN_HEIGHT - map->textures->right_hand->height));
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_destroy_image(win->mlx_ptr, minimap->img_ptr);
	free(minimap);
}
