#include "cube.h"

void	paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos)
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

void	draw_minimap_ray(t_map *map, t_image *image, int zoom)
{
	t_vector2	start = ft_vector2((MINIMAP_RENDER_DISTANCE / 2) * zoom, (MINIMAP_RENDER_DISTANCE / 2) * zoom);

	t_vector2	end = ft_vector2((MINIMAP_RENDER_DISTANCE / 2) * zoom + cos(map->player.dir) * zoom,
								  (MINIMAP_RENDER_DISTANCE / 2) * zoom + sin(map->player.dir) * zoom);

	draw_circle(image, start, zoom / 4, HEX_BLUE);

	ft_draw_line(image, ft_line(start, end, HEX_RED, 1));
}

void	draw_minimap_player(t_image *image, int zoom)
{
	draw_circle(image,
				ft_vector2((MINIMAP_RENDER_DISTANCE / 2) * zoom, (MINIMAP_RENDER_DISTANCE / 2) * zoom),
				zoom / 4,
				HEX_RED
	);
}

t_image	*draw_minimap(t_map *map, void *mlx_ptr, int zoom)
{
	t_image	*image;
	int		i;
	int		j;
	double		start_x, start_y;
	double		end_x, end_y;
	double		offset_x, offset_y;

	image = ft_init_image(mlx_ptr, MINIMAP_RENDER_DISTANCE * zoom, MINIMAP_RENDER_DISTANCE * zoom);
	if (!image)
		return (NULL);

	start_x = map->player.x - (MINIMAP_RENDER_DISTANCE / 2);
	start_y = map->player.y - (MINIMAP_RENDER_DISTANCE / 2);
	end_x = start_x + MINIMAP_RENDER_DISTANCE;
	end_y = start_y + MINIMAP_RENDER_DISTANCE;

	j = start_y;
	while (j < end_y)
	{
		i = start_x;
		while (i < end_x)
		{
			offset_x = (i - start_x) * zoom;
			offset_y = (j - start_y) * zoom;
			if (i >= 0 && i < map->size_x && j >= 0 && j < map->size_y)
			{
				if (map->blocks[j][i].type == WALL)
					draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_BLACK);
				else
					draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_WHITE);
			}
			else
				draw_square(image, ft_vector2(offset_x, offset_y), zoom, HEX_BLACK);
			i++;
		}
		j++;
	}
	draw_minimap_player(image, zoom);
	draw_minimap_ray(map, image, zoom);
	return (image);
}


/**
 * @brief Refresh the screen with the new image.
 *
 * @param t_win *win The window to refresh.
 * @param t_map *map The map to render.
 */
void	refresh(t_win *win, t_map *map)
{
	int		zoom;
	t_image	*minimap;

	zoom = 20;
	/////////

	minimap = draw_minimap(map, win->mlx_ptr, zoom);
	if (!minimap)
		return;
	paste_image_on_screen(win, minimap, ft_vector2(0, 0));
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_destroy_image(win->mlx_ptr, minimap->img_ptr);
	free(minimap);
}
