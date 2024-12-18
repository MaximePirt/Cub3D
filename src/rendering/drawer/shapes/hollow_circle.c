#include "cube.h"

void draw_hollow_circle(t_image *image, t_vector2 pos, int radius, int line_width, int color)
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
				ft_draw_pixel_on_image(image, pos.x + i, pos.y + j, color);
            j++;
        }
        i++;
    }
}