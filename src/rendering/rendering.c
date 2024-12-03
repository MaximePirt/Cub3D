#include "cube.h"

void	paste_image_on_image(t_win *win, t_image *image, int x, int y)
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
			ft_draw_pixel(win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

/**
 * @brief Generate a mini map to show what's around the player.
 * 			The distance limit is 15 blocks.
 * 			The mini map is 30x30 blocks.
 * 				- 10 pixels per block
 * 			The mini map is centered on the player.
 * 			The mini map will be drawn in the top left corner of the screen.
 *
 * @param win
 * @param map
 */
void	draw_mini_map(t_win *win, t_map *map, int distance)
{
	int i;
	int j;
	int x;
	int y;

	i = map->player.x - distance;
	while (i < map->player.x + distance)
	{
		j = map->player.y - distance;
		while (j < map->player.y + distance)
		{
			x = (i - map->player.x + distance) * 10;
			y = (j - map->player.y + distance) * 10;
			if (i >= 0 && i < map->size_x && j >= 0 && j < map->size_y)
			{
				if (map->blocks[j][i].type == WALL)
					draw_square(win, ft_vector2(x, y), 10, HEX_BLACK);
				else
					draw_square(win, ft_vector2(x, y), 10, HEX_WHITE);
			}
			else
				draw_square(win, ft_vector2(x, y), 10, HEX_BLACK);
			j++;
		}
		i++;
	}
	draw_circle(win, ft_vector2(150, 150), 5, HEX_RED);
	// set transparency to 0x00 for a hollow circle
	draw_hollow_circle(win, ft_vector2(50, 50), 100, 10, 0xff0000f2);
}

void	refresh(t_win *win, t_map *map)
{
	paste_image_on_image(win, map->textures->wall_north, 0, 0);
	draw_mini_map(win, map, 15);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}