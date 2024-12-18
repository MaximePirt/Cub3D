#include "cube.h"

void draw_circle(t_image *image, t_vector2 pos, int radius, int color)
{
	int	x;
	int	y;
	int	sq_radius;

	sq_radius = radius * radius;
	x = -radius;
	while (x <= radius)
	{
		y = -radius;
		while (y <= radius)
		{
			if (x * x + y * y <= sq_radius)
				ft_draw_pixel_on_image(image, ft_vector2(pos.x + x, pos.y + y), color);
			y++;
		}
		x++;
	}
}
