#include "cube.h"

void	ft_draw_pixel(t_win *win, int x, int y, int color)
{
	*(int *)(win->img_data + ((int)x * win->bpp / 8) + ((int)y * win->size_line)) = color;
}

void	draw_square(t_win *win, t_vector2 pos, int size, int color)

{
	int i;
	int j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_draw_pixel(win, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

void draw_circle(t_win *win, t_vector2 pos, int radius, int color)
{
	int i;
	int j;

	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			if (sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius)) < radius)
				ft_draw_pixel(win, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}

void draw_hollow_circle(t_win *win, t_vector2 pos, int radius, int line_width, int color)
{
	int i;
	int j;

	i = 0;
	while (i < radius * 2)
	{
		j = 0;
		while (j < radius * 2)
		{
			if (sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius)) < radius &&
				sqrt((i - radius) * (i - radius) + (j - radius) * (j - radius)) > radius - line_width)
				ft_draw_pixel(win, pos.x + i, pos.y + j, color);
			j++;
		}
		i++;
	}
}