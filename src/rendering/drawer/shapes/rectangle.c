#include "cube.h"

void	draw_rectangle(t_win *win, t_vector2 pos, int width, int height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width)
	{
		j = 0;
		while (j < height)
		{
			ft_draw_pixel_on_screen(
				win, ft_vector2(pos.x + i, pos.y + j), color);
			j++;
		}
		i++;
	}
}
