/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rectangle.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2024/12/01 06:13:17 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

void	draw_rectangle(t_win *win, t_vector2 pos,
		t_vector2 width_height, int color)
{
	int	i;
	int	j;

	i = 0;
	while (i < width_height.x)
	{
		j = 0;
		while (j < width_height.y)
		{
			ft_draw_pixel_on_screen(
				win, ft_vector2(pos.x + i, pos.y + j), color);
			j++;
		}
		i++;
	}
}
