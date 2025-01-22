#include "cube.h"

void	draw_rectangle(t_win *win, t_vector2 pos,
		t_vector2 width_height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width_height.x)
	{
		j = 0;
		while (j < width_height.y)
		{
			ft_draw_pixel_on_screen(
				win, ft_vector2(pos.x + i, pos.y + j), color);
			j++;
		}
		i++;
	}
}
