/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_free_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/26 19:00:02 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

void	*ft_free_rays(t_ray *rays)
{
	t_ray	*tmp;

	while (rays)
	{
		tmp = rays;
		rays = rays->next;
		free(tmp);
	}
	return (NULL);
}

void	free_images(char **images)
{
	int i;
	
	i = 0;
	while (i < 6)
		free(images[i++]);
	free(images);
	return ;
}
