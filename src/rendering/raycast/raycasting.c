/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:35:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/17 14:30:35 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
* TODO: Remove this comment
*	In map, struct ray will contain every ray that will be casted,
*	It will be sent to the minimap by the struct map
*	On this file, i need to work on the raycasting calcul
*	We base our raycasting by sending the first ray from the player with
*	a 0dg angle, then draw them from middle to right, then from left to middle
*	The struct is double linked, we can imagined it like a circle, middle to right, then left to middle
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
#define DEG_TO_RAD(angleDegrees) ((angleDegrees) * M_PI / 180.0)

void	process_ray(t_map *map, t_ray *ray, int ray_index) {
	double add_angle = (ray_index * (FOV / (double)RAYS_COUNT)) - (FOV / 2);
	double angle = map->player.dir + add_angle;

	double ray_dirX = cos(DEG_TO_RAD(angle));
	double ray_dirY = sin(DEG_TO_RAD(angle));

	double posX = map->player.x;
	double posY = map->player.y;

	int mapX = (int)posX;
	int mapY = (int)posY;

	double deltaDistX = (ray_dirX == 0) ? 1e30 : fabs(1 / ray_dirX);
	double deltaDistY = (ray_dirY == 0) ? 1e30 : fabs(1 / ray_dirY);

	int stepX, stepY;
	double sideDistX, sideDistY;

	if (ray_dirX < 0) {
		stepX = -1;
		sideDistX = (posX - mapX) * deltaDistX;
	} else {
		stepX = 1;
		sideDistX = (mapX + 1.0 - posX) * deltaDistX;
	}
	if (ray_dirY < 0) {
		stepY = -1;
		sideDistY = (posY - mapY) * deltaDistY;
	} else {
		stepY = 1;
		sideDistY = (mapY + 1.0 - posY) * deltaDistY;
	}

	int hit = 0;
	int side = 0;
	while (hit == 0) {

		if (sideDistX < sideDistY) {
			sideDistX += deltaDistX;
			mapX += stepX;
			side = 0;
		} else {
			sideDistY += deltaDistY;
			mapY += stepY;
			side = 1;
		}
		ray->type = FLOOR;
		if (map->blocks[mapY][mapX].type == WALL)
			hit = 1;
		else if (map->blocks[mapY][mapX].type == DOOR && map->blocks[mapY][mapX].status == 1) {
			hit = 1;
			ray->type = DOOR;
		}
		else
			hit = 0;
	}

	double perpWallDist;
	if (side == 0) {
		perpWallDist = (mapX - posX + (1 - stepX) / 2) / ray_dirX;
	} else {
		perpWallDist = (mapY - posY + (1 - stepY) / 2) / ray_dirY;
	}

	ray->distance = perpWallDist;
	ray->x_axis = side == 0 ? posY + perpWallDist * ray_dirY : posX + perpWallDist * ray_dirX;
	ray->x_axis = ray->x_axis - (int)ray->x_axis;
}


/**
 * @brief Cast all rays for the player's field of view and calculate distances.
 * @param map The map containing ray and block data.
 * @return int Status code (0 for success).
 */
int give_all_rays(t_map *map)
{
	int i = 0;
	t_ray *tmp = map->rays;

	while (i < RAYS_COUNT)
	{
		process_ray(map, tmp, i);
		tmp = tmp->next;
		i++;
	}

	return 0;
}