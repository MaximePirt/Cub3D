#include "cube.h"

void	ft_draw_pixel_on_image(t_image *image, int x, int y, int color)
{
    if (x < 0 || x >= image->width || y < 0 || y >= image->height)
        return ;
    *(int *)(image->img_data + ((int)x * image->bpp / 8) + ((int)y * image->size_line)) = color;
}

void	ft_draw_pixel_on_screen(t_win *win, int x, int y, int color)
{
	if (x < 0 || x >= SCREEN_WIDTH || y < 0 || y >= SCREEN_HEIGHT)
		return ;
	*(int *)(win->img_data + x * win->bpp / 8 + y * win->size_line) = color;
}
