/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycasting.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/18 04:35:29 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/14 14:50:43 by mpierrot         ###   ########.fr       */
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
	double length;
	double x_end;
	(void) x_end;
	(void) y_start;

	x_tan = tan(angle * M_PI / 180);
	y_var = 1;
	x_var = y_var / x_tan;
	x_end = x_start / x_var; 
	printf("Xend : [%f]\n", x_end);
	length = sqrt(x_var * x_var + y_var * y_var);
	(*ray)->distance = length;
	return (length);
	
}


int give_all_rays(t_map *map)
{
	int i;
	double	x_start;
	double	y_start;
	t_ray	*tmp;
	double length;
	(void) length;
	// printf("Enter here\n"); 
	i = 0;
	tmp = map->rays;
	while (i < RAYS_COUNT)
	{
		x_start = map->player.x;
		y_start = map->player.y;
		while (&map->blocks[(int)x_start][(int)y_start] && map->blocks[(int)x_start][(int)y_start].type != WALL)
		{
			// double tqt = (map->player.dir + (i * ANGLE) - (FOV / 2)) * M_PI / 180.0;
			printf("Angle [%d] distance [%f]\n", ANGLE, tmp->distance);

			// printf("ray id [%d]\n xstart %f\n ystart %f\n-------\n", tmp->id, x_start, y_start);
			length = find_finale_x(&tmp, ANGLE, x_start, y_start);
			x_start +=1;
			y_start +=1;		

		}
		printf("Ray id [%d] distance [%f]\n", tmp->id, tmp->distance);
		tmp = tmp->next;
		i++;
	}
	// printf("Out here\n");
	
  return (0);
}
