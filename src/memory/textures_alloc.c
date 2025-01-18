#include "cube.h"

static t_image	*ft_init_texture(t_image **image)
{

	*image = (t_image *)malloc(sizeof(t_image));
	if (*image == NULL)
		return (NULL);
	(*image)->path = NULL;
	(*image)->img_ptr = NULL;
	(*image)->img_data = NULL;
	(*image)->bpp = 0;
	(*image)->size_line = 0;
	(*image)->endian = 0;
	(*image)->width = 0;
	(*image)->height = 0;
	return (*image);
}

t_textures	*ft_init_textures(void)
{
	t_textures	*textures;

	textures = (t_textures *)malloc(sizeof(t_textures));
	if (!textures)
		return (NULL);
	if (!ft_init_texture(&textures->wall_north) ||
		!ft_init_texture(&textures->wall_south) ||
		!ft_init_texture(&textures->wall_east) ||
		!ft_init_texture(&textures->wall_west) ||
		!ft_init_texture(&textures->door) ||
		!ft_init_texture(&textures->right_hand))
	{
		free(textures);
		return (NULL);
	}
	return (textures);
}