/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:35:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/25 02:49:45 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

static void	struct_fill_forest(t_calcul_ray *calcul)
{
	if (calcul->ray_dirx < 0)
	{
		calcul->stepx = -1;
		calcul->sidedistx = (calcul->posx - calcul->mapx) * calcul->deltadistx;
	}
	else
	{
		calcul->stepx = 1;
		calcul->sidedistx = (calcul->mapx + 1.0 - calcul->posx)
			* calcul->deltadistx;
	}
	if (calcul->ray_diry < 0)
	{
		calcul->stepy = -1;
		calcul->sidedisty = (calcul->posy - calcul->mapy) * calcul->deltadisty;
	}
	else
	{
		calcul->stepy = 1;
		calcul->sidedisty = (calcul->mapy + 1.0 - calcul->posy)
			* calcul->deltadisty;
	}
}

static void	struct_filler(t_calcul_ray *calcul, t_map *map, int ray_index)
{
	calcul->add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	calcul->angle = map->player.dir + calcul->add_angle;
	calcul->ray_dirx = cos((calcul->angle) * M_PI / 180.0);
	calcul->ray_diry = sin((calcul->angle)*M_PI / 180.0);
	calcul->posx = map->player.x;
	calcul->posy = map->player.y;
	calcul->mapx = (int)calcul->posx;
	calcul->mapy = (int)calcul->posy;
	calcul->hit = 0;
	calcul->side = 0;
	if (calcul->ray_dirx == 0)
		calcul->deltadistx = 1e30;
	else
		calcul->deltadistx = fabs(1 / calcul->ray_dirx);
	if (calcul->ray_diry == 0)
		calcul->deltadisty = 1e30;
	else
		calcul->deltadisty = fabs(1 / calcul->ray_diry);
	struct_fill_forest(calcul);
}

static void	hit_loop(t_calcul_ray *calcul, t_map *map, t_ray *ray)
{
	while (calcul->hit == 0)
	{
		if (calcul->sidedistx < calcul->sidedisty)
		{
			calcul->sidedistx += calcul->deltadistx;
			calcul->mapx += calcul->stepx;
			calcul->side = 0;
		}
		else
		{
			calcul->sidedisty += calcul->deltadisty;
			calcul->mapy += calcul->stepy;
			calcul->side = 1;
		}
		ray->type = FLOOR;
		calcul->hit = 0;
		if (map->blocks[calcul->mapy][calcul->mapx].type == WALL)
			calcul->hit = 1;
		else if (map->blocks[calcul->mapy][calcul->mapx].type == DOOR
			&& map->blocks[calcul->mapy][calcul->mapx].status == 1)
		{
			calcul->hit = 1;
			ray->type = DOOR;
		}
	}
}

void	process_ray(t_map *map, t_ray *ray, int ray_index)
{
	t_calcul_ray	calcul;

	struct_filler(&calcul, map, ray_index);
	ray->angle = calcul.angle;
	hit_loop(&calcul, map, ray);
	if (calcul.side == 0)
		calcul.perpwalldist = (calcul.mapx - calcul.posx + (1 - calcul.stepx)
				/ 2) / calcul.ray_dirx;
	else
		calcul.perpwalldist = (calcul.mapy - calcul.posy + (1 - calcul.stepy)
				/ 2) / calcul.ray_diry;
	ray->distance = calcul.perpwalldist;
	if (calcul.side == 0)
		ray->x_axis = calcul.posy + calcul.perpwalldist * calcul.ray_diry;
	else
		ray->x_axis = calcul.posx + calcul.perpwalldist * calcul.ray_dirx;
	ray->x_axis = ray->x_axis - (int)ray->x_axis;
	ray->side = calcul.side;
}

/**
 * @brief Cast all rays for the player's field of view and calculate distances.
 * @param map The map containing ray and block data.
 * @return int Status code (0 for success).
 */
int	give_all_rays(t_map *map)
{
	int		i;
	t_ray	*tmp;

	i = 0;
	tmp = map->rays;
	while (i < RAYS_COUNT)
	{
		process_ray(map, tmp, i);
		tmp = tmp->next;
		i++;
	}
	return (0);
}
