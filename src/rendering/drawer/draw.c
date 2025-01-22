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
