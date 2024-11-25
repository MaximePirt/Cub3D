#include "cube.h"

/**
* @brief Load the texture
* @param image the image
* @param path the path
* @param mlx_ptr the mlx ptr
*/
void	load_texture(t_image *image, char *path, void *mlx_ptr)
{
	image->path = ft_strdup(path);
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &image->width, &image->height);
	image->img_data = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->size_line, &image->endian);
}
