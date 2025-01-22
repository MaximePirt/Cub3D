#include "cube.h"

void	draw_square(t_image *img, t_vector2 pos, int size, int color)

{
	int	i;
	int	j;

	i = 0;
	while (i < size)
	{
		j = 0;
		while (j < size)
		{
			ft_draw_pixel_on_image(
				img, ft_vector2(pos.x + i, pos.y + j), color);
			j++;
		}
		i++;
	}
}
