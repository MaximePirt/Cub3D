/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   image_tools_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:40:52 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	paste_image_on_screen(t_win *win, t_image *image, t_vector2 pos)
{
	int	i;
	int	j;
	int	color;
	int	alpha;

	i = 0;
	while (i < image->width)
	{
		j = 0;
		while (j < image->height)
		{
			color = *(int *)(image->img_data + (i * image->bpp / 8)
					+ (j * image->size_line));
			alpha = (color >> 24) & 0xFF;
			if (pos.x < 0 || pos.x >= SCREEN_WIDTH
				|| pos.y < 0 || pos.y >= SCREEN_HEIGHT)
				return ;
			if (alpha == 0)
				*(int *)(win->img_data + ((int)pos.x + i)
						* win->bpp / 8 + ((int)pos.y + j)
						* win->size_line) = color;
			j++;
		}
		i++;
	}
}

/**
 * @brief Draw a square on the image
 * @param img the image
 * @param color the color
 */
void	ft_fill_image(t_image *img, int color)
{
	int	i;

	i = 0;
	while (i < img->width * img->height)
	{
		((int *)img->img_data)[i] = color;
		i++;
	}
}
