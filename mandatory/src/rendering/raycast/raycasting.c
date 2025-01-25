/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:35:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/19 16:18:27 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

static void	struct_fill_forest(t_calcul_ray *calcul)
{
	if (calcul->ray_dirX < 0)
	{
		calcul->stepX = -1;
		calcul->sideDistX = (calcul->posX - calcul->mapX) * calcul->deltaDistX;
	}
	else
	{
		calcul->stepX = 1;
		calcul->sideDistX = (calcul->mapX + 1.0 - calcul->posX)
			* calcul->deltaDistX;
	}
	if (calcul->ray_dirY < 0)
	{
		calcul->stepY = -1;
		calcul->sideDistY = (calcul->posY - calcul->mapY) * calcul->deltaDistY;
	}
	else
	{
		calcul->stepY = 1;
		calcul->sideDistY = (calcul->mapY + 1.0 - calcul->posY)
			* calcul->deltaDistY;
	}
}

static void	struct_filler(t_calcul_ray *calcul, t_map *map, int ray_index)
{
	calcul->add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	calcul->angle = map->player.dir + calcul->add_angle;
	calcul->ray_dirX = cos(DEG_TO_RAD(calcul->angle));
	calcul->ray_dirY = sin(DEG_TO_RAD(calcul->angle));
	calcul->posX = map->player.x;
	calcul->posY = map->player.y;
	calcul->mapX = (int)calcul->posX;
	calcul->mapY = (int)calcul->posY;
	calcul->hit = 0;
	calcul->side = 0;
	if (calcul->ray_dirX == 0)
		calcul->deltaDistX = 1e30;
	else
		calcul->deltaDistX = fabs(1 / calcul->ray_dirX);
	if (calcul->ray_dirY == 0)
		calcul->deltaDistY = 1e30;
	else
		calcul->deltaDistY = fabs(1 / calcul->ray_dirY);
	struct_fill_forest(calcul);
}

static void	hit_loop(t_calcul_ray *calcul, t_map *map, t_ray *ray)
{
	while (calcul->hit == 0)
	{
		if (calcul->sideDistX < calcul->sideDistY)
		{
			calcul->sideDistX += calcul->deltaDistX;
			calcul->mapX += calcul->stepX;
			calcul->side = 0;
		}
		else
		{
			calcul->sideDistY += calcul->deltaDistY;
			calcul->mapY += calcul->stepY;
			calcul->side = 1;
		}
		ray->type = FLOOR;
		calcul->hit = 0;
        if (calcul->mapX < 0 || calcul->mapY < 0 || calcul->mapX >= map->size_x || calcul->mapY >= map->size_y)
        {
            calcul->hit = 1;
            ray->type = WALL;
        }
		else if (map->blocks[calcul->mapY][calcul->mapX].type == WALL)
			calcul->hit = 1;
	}
}

void	process_ray(t_map *map, t_ray *ray, int ray_index)
{
	t_calcul_ray	calcul;

	struct_filler(&calcul, map, ray_index);
	ray->angle = calcul.angle;
	hit_loop(&calcul, map, ray);
	if (calcul.side == 0)
		calcul.perpWallDist = (calcul.mapX - calcul.posX + (1 - calcul.stepX)
				/ 2) / calcul.ray_dirX;
	else
		calcul.perpWallDist = (calcul.mapY - calcul.posY + (1 - calcul.stepY)
				/ 2) / calcul.ray_dirY;
	ray->distance = calcul.perpWallDist;
	if (calcul.side == 0)
		ray->x_axis = calcul.posY + calcul.perpWallDist * calcul.ray_dirY;
	else
		ray->x_axis = calcul.posX + calcul.perpWallDist * calcul.ray_dirX;
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
