/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   circle_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:40:40 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	draw_circle(t_image *img, t_vector2 pos, int radius, int color)
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
				ft_draw_pixel_on_image(
					img, ft_vector2(pos.x + x, pos.y + y), color);
			y++;
		}
		x++;
	}
}
