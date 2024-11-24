#include "cube.h"

void	ft_draw_pixel(t_win *win, int x, int y, int color)
{
	*(int *)(win->img_data + ((int)x * win->bpp / 8) + ((int)y * win->size_line)) = color;
}

static	void draw_square(t_win *win, int x, int y, int size, int color)
{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_draw_pixel(win, x + i, y + j, color);
			j++;
		}
		i++;
	}
}

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

void	refresh(t_win *win, t_map *map)
{
	paste_image_on_image(win, map->textures->wall_north, 0, 0);
	draw_square(win, SCREEN_WIDTH / 2.5, SCREEN_HEIGHT / 3.5, 100, HEX_RED);
	draw_square(win, SCREEN_WIDTH / 1.68, SCREEN_HEIGHT / 3.5, 100, HEX_RED);
	draw_square(win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 100, HEX_RED);
	draw_square(win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2.5, 100, HEX_RED);
	draw_square(win, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 3, 100, HEX_RED);
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
}