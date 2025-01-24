/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_alloc_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:39:45 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

t_image	*ft_init_image(void *mlx_ptr, int width, int height)
{
	t_image	*image;

	image = (t_image *)malloc(sizeof(t_image));
	if (!image)
		return (NULL);
	image->path = NULL;
	image->bpp = 0;
	image->endian = 0;
	image->width = width;
	image->height = height;
	image->img_ptr = mlx_new_image(mlx_ptr, width, height);
	if (!image->img_ptr)
	{
		free(image);
		return (NULL);
	}
	image->img_data = mlx_get_data_addr(image->img_ptr,
			&image->bpp, &image->size_line, &image->endian);
	if (!image->img_data)
	{
		mlx_destroy_image(mlx_ptr, image->img_ptr);
		free(image);
		return (NULL);
	}
	return (image);
}
