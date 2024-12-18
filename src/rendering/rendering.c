#include "cube.h"

void	paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos)
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

			if (pos.x < 0 || pos.x >= SCREEN_WIDTH || pos.y < 0 || pos.y >= SCREEN_HEIGHT)
				return ;
			*(int *)(win->img_data + ((int)pos.x + i) * win->bpp / 8 + ((int)pos.y + j) * win->size_line) = color;
			j++;
		}
		i++;
	}
}

/**
 * @brief Refresh the screen with the new image.
 *
 * @param t_win *win The window to refresh.
 * @param t_map *map The map to render.
 */
void	refresh(t_win *win, t_map *map)
{
	t_image	*minimap;

	minimap = draw_minimap(map, win->mlx_ptr);
	if (!minimap)
		return;
	//code here
	give_all_rays(map);
	paste_image_on_screen(win, minimap, ft_vector2(0, 0));
	mlx_put_image_to_window(win->mlx_ptr, win->win_ptr, win->img_ptr, 0, 0);
	mlx_destroy_image(win->mlx_ptr, minimap->img_ptr);
	free(minimap);
}
