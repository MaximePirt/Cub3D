/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:12:29 by julthoma          #+#    #+#             */
/*   Updated: 2025/01/22 17:30:13 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

// static int	extract_image_pixel(t_image *texture, t_vector2 pos)
// {
// 	int	color;

// 	if (pos.x < 0 || pos.x >= texture->width
// 		|| pos.y < 0 || pos.y >= texture->height)
// 		return (0);
// 	color = *(int *)(texture->img_data + (int)pos.y \
// 		* texture->size_line + (int)pos.x * (texture->bpp / 8));
// 	return (color);
// }

// void	copy_vertical_pixels(t_image *img, t_image *texture, t_vector2 pos, int height, int width, int texture_x)
// {
// 	int			i;
// 	int			j;
// 	int			color;
// 	t_vector2	new_pos;

// 	i = texture_x;
// 	while (i < width + texture_x)
// 	{
// 		j = 0;
// 		while (j < height)
// 		{
// 			color = extract_image_pixel(texture, ft_vector2(i, j));
// 			new_pos = ft_vector2(pos.x + i, pos.y + j);
// 			if (new_pos.x < 0 || new_pos.x >= SCREEN_WIDTH
// 				|| new_pos.y < 0 || new_pos.y >= SCREEN_HEIGHT)
// 				return ;
// 			*(int *)(img->img_data + (int)new_pos.y \
// 				* img->size_line + (int)new_pos.x * (img->bpp / 8)) = color;
// 			j++;
// 		}
// 		i++;
// 	}
// }
