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

#define DEG_TO_RAD(angleDegrees) ((angleDegrees)*M_PI / 180.0)

/**
* TODO: Remove this comment
*	In map, struct ray will contain every ray that will be casted,
*	It will be sent to the minimap by the struct map
*	On this file, i need to work on the raycasting calcul
*	We base our raycasting by sending the first ray from the player with
*	a 0dg angle, then draw them from middle to right, then from left to middle
*	The struct is double linked, we can imagined it like a circle,
		middle to right, then left to middle
*	How proceed :
*	1. send first ray with 0 angle
*	2. send ray from (pi/2) - FOV/2

while y +1 != wall && xfin + 1 != wall

How to calculate :
	- Find finale position x where ray hit 1
	- find ray size (hypothenuse)
	tan(angle) = vary/varx
	=> varx = vary/tan(angle)
	=> vary= 1-0
	=> angle = 20degre ( in reality its define)
	varxfin = varxdepart/varx
	varxfin = vardepart/ (vary/tan(angle))
exemple
	varxfin = 0.2/ (1/tan(20))
	varxfin = 0.56

ray size : pythagore
longueur = sqrt(varx^2 + vary^2)
exemple :
	longueur = sqrt(0.2^2 + 1^2)
	longueur = sqrt(0.04 + 1)
	longueur = sqrt(1.04)
	longueur = 1.02
*/

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
		if (map->blocks[calcul->mapY][calcul->mapX].type == WALL)
			calcul->hit = 1;
		else if (map->blocks[calcul->mapY][calcul->mapX].type == DOOR
			&& map->blocks[calcul->mapY][calcul->mapX].status == 1)
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
}

/**
 * @brief Cast all rays for the player's field of view and calculate distances.
 * @param map The map containing ray and block data.
 * @return int Status code (0 for success).
 */
int	give_all_rays(t_map *map)
{
	int i = 0;
	t_ray *tmp = map->rays;

	while (i < RAYS_COUNT)
	{
		process_ray(map, tmp, i);
		tmp = tmp->next;
		i++;
	}

	return (0);
}