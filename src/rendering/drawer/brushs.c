#include "cube.h"

void	ft_draw_pixel_on_image(t_image *image, t_vector2 pos, int color)
{
	if (pos.x < 0 || pos.x >= image->width
		|| pos.y < 0 || pos.y >= image->height)
		return ;
	*(int *)(image->img_data + ((int)pos.x * image->bpp / 8) \
		+ ((int)pos.y * image->size_line)) = color;
}

void	ft_draw_pixel_on_screen(t_win *win, t_vector2 pos, int color)
{
	*(int *)(win->img_data + ((int)pos.x * win->bpp / 8) \
		+ ((int)pos.y * win->size_line)) = color;
}

void	ft_draw_line(t_image *img, t_line line)
{
	t_vector2	delta;
	t_vector2	current_point;
	double		steps;
	double		i;
	double		w;

	delta.x = line.end.x - line.start.x;
	delta.y = line.end.y - line.start.y;
	if (fabs(delta.x) > fabs(delta.y))
		steps = fabs(delta.x);
	else
		steps = fabs(delta.y);
	w = -(line.width / 2.0);
	while (w <= (line.width / 2.0))
	{
		i = 0.0;
		while (i <= steps)
		{
			current_point.x = line.start.x + (delta.x * i) / steps;
			current_point.y = line.start.y + (delta.y * i) / steps;
			if (fabs(delta.x) > fabs(delta.y))
				ft_draw_pixel_on_image(img, ft_vector2(current_point.x, current_point.y + w), line.color);
			else
				ft_draw_pixel_on_image(img, ft_vector2(current_point.x + w, current_point.y), line.color);
			i += 1.0;
		}
		w += 1.0;
	}
}

int	get_pixel_color(t_image *texture, t_vector2 pos)
{
	int	color;

	if (pos.x < 0 || pos.x >= texture->width
		|| pos.y < 0 || pos.y >= texture->height)
		return (0);
	color = *(int *)(texture->img_data + (int)pos.y * texture->size_line
			+ (int)pos.x * (texture->bpp / 8));
	return (color);
}

void	set_pixel_color(t_win *win, t_vector2 pos, int color)
{
	if (pos.x < 0 || pos.x >= SCREEN_WIDTH
		|| pos.y < 0 || pos.y >= SCREEN_HEIGHT)
		return ;
	*(int *)(win->img_data + (int)pos.y * win->size_line
			+ (int)pos.x * (win->bpp / 8)) = color;
}
