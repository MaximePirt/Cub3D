/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_alloc_bonus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 04:12:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/24 00:39:52 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static t_ray	*ft_init_ray(void)
{
	t_ray	*ray;

	ray = (t_ray *)malloc(sizeof(t_ray));
	if (!ray)
		return (NULL);
	ray->distance = 1;
	ray->x_axis = 0;
	ray->next = NULL;
	ray->prev = NULL;
	return (ray);
}

t_ray	*ft_init_rays(void)
{
	t_ray	*head;
	t_ray	*current;
	t_ray	*prev;
	int		i;

	head = NULL;
	prev = NULL;
	i = 0;
	while (i < RAYS_COUNT)
	{
		current = ft_init_ray();
		if (!current)
		{
			ft_free_rays(head);
			return (NULL);
		}
		current->prev = prev;
		if (prev)
			prev->next = current;
		else
			head = current;
		prev = current;
		i++;
	}
	return (head);
}
