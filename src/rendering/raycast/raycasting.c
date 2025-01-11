/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:35:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/10 19:21:19 by mpierrot         ###   ########.fr       */
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

#include <math.h>

double	calculate_ray_size(t_ray **ray, double x_var, double y_var)
{
	double length;

	length = sqrt(x_var * x_var + y_var * y_var);
	// ray->distance = length;
		(*ray)->distance = 5000;

	//printf("Length : [%f]\n", length);
	return (length);
	
}

/**
 * 	@brief Search finale x position, then calculate x size
 * 
 *		y start is at first players y position then position which we stopped
 */
double	find_finale_x(t_ray **ray, int angle, double x_start, double y_start)
{
	double	x_var;
	double	y_var;
	double	x_tan;
	double	x_end;
	(void) y_start;
	(void) x_end;

	x_tan = tan(angle * M_PI / 180);
	y_var = 1;
	x_var = y_var / x_tan;
	x_end = x_start / x_var;
	//printf("Xend : [%f]\n", x_end);
	return (calculate_ray_size(ray, x_var, y_var));
	
}

int give_all_rays(t_map *map)
{
	int i;
	double	x_start;
	double	y_start;
	t_ray	*tmp;
	
	x_start = map->player.x;
	y_start = map->player.y;
	//printf("Enter here");
	i = 0;
	tmp = map->rays;
	while (i < RAYS_COUNT)
	{
		//printf("ray id [%d]\n", tmp->id);
		while ((map->blocks[(int)x_start] && map->blocks[(int)x_start + 1][(int)y_start].type != WALL )
			&& (map->blocks[(int)x_start][(int)y_start + 1].type &&  map->blocks[(int)x_start][(int)y_start + 1].type != WALL ))
		{
			//printf("ray id [%d], xstart %f, ystart %f\n", tmp->id, x_start, y_start);
			find_finale_x(&tmp, ANGLE, x_start, y_start);
			x_start +=1;
			y_start +=1;		
		}
		tmp = tmp->next;
		i++;
	}
	//printf("Out here\n");

//   i = 0;
//   while (i < RAYS_COUNT)
//   {
	
// 	i++;
//   }
  return (0);
}
