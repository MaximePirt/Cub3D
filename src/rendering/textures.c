#include "cube.h"

/**
* @brief Check paths and load the texture
* @param image the image
* @param path the path
* @param mlx_ptr the mlx ptr
*/
int	load_texture(t_image *image, char *path, void *mlx_ptr)
{
	char	**tmp;
	int		fd;

	tmp = ft_split(path, "");
	image->path = ft_strdup(tmp[1]);
	fd = open(image->path, O_RDONLY);
	if (fd == -1)
	{
		ft_printf("Error: invalid texture path\n");
		return (1);
	}
	close(fd);
	image->img_ptr = mlx_xpm_file_to_image(mlx_ptr, path, &image->width, &image->height);
	image->img_data = mlx_get_data_addr(image->img_ptr, &image->bpp, &image->size_line, &image->endian);
	return (0);
}
int	fill_rgb_texture(t_rgb *items, char *value)
{
	char **tmp;
	int i;
	int	converted;

	i = 1;
	tmp = ft_split_quote(value, " ,", "\"");
	if (!tmp)
		return (1);
	while (tmp[i])
	{
		if (!ft_str_is_digit(tmp[i]))
		{
			ft_printf("Error: invalid color value\n");
			return (1);
		}
		converted = ft_atoi(tmp[i]);
		if (converted < 0 || converted > 255)
		{
			ft_printf("Error: invalid color value\n");
			return (1);
		}
		if (i == 1)
			items->r = converted;
		else if (i == 2)
		items->g = converted;
		else if (i == 3)
		items->b = converted;
		i++;
	}
	return (0);
}
