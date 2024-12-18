#include "cube.h"

t_image *ft_init_image(void *mlx_ptr, int width, int height)
{
	t_image *image;

	if (!(image = (t_image *)malloc(sizeof(t_image))))
		return (NULL);
	image->path = NULL;
	image->bpp = 0;
	image->size_line = 0;
	image->endian = 0;
	image->width = width;
	image->height = height;
	image->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image->img_ptr)
	{
		free(image);
		return (NULL);
	}
	image->img_data = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->size_line, &image->endian);
	if (!image->img_data)
	{
		mlx_destroy_image(mlx_ptr, image->img_ptr);
		free(image);
		return (NULL);
	}
	return (image);
}
