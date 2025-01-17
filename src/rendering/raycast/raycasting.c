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
	double length;
	double x_end;
	(void) x_end;
	(void) y_start;
	(void) x_end;

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
	// double	x_start;
	// double	y_start;
	double arctan;
	t_ray	*tmp;
	double length;
	double pos_x;
	double pos_y;
	double y_offset;
	double x_offset;
	int pos_r_mx;
	int pos_r_my;
	int pos_r_mp;
	(void) pos_r_mp;
	(void) pos_r_mx;
	(void) pos_r_my;
	(void) y_offset;
	(void) x_offset;
	(void) pos_x;
	(void) pos_y;
	(void) length;
	// printf("Enter here\n"); 
	i = 0;
	tmp = map->rays;
	// while (i < RAYS_COUNT)
	// {
		fprintf(stderr, "debug1\n");
		int stop = 0;

		tmp->angle = i * ANGLE;
		arctan = -1/tan(tmp->angle);		
		//look up
		if (tmp->angle > M_PI)
		{
			pos_y = ceil(map->player.y) - 0.0001;
			pos_x = map->player.y - pos_y * arctan + map->player.x;
			y_offset = -64;
			x_offset = y_offset * arctan;
		}
		fprintf(stderr, "debug2\n");
		//look down
		if (tmp->angle < M_PI)
		{
			pos_y = ceil(map->player.y) + 64;
			pos_x = map->player.y - pos_y * arctan + map->player.x;
			y_offset = 64;
			x_offset = y_offset * arctan;
		}
		fprintf(stderr, "debug3\n");
		//look left/right
		if (tmp->angle == 0 || tmp->angle == M_PI)
		{
			pos_x = map->player.x;
			pos_x = map->player.y;
			stop = 8;
		}
		printf("debug4\n");
		while (stop < 8)
		{
			printf("debug5\n");
			pos_r_mx = (int) pos_x / 64;
			pos_r_my = (int) pos_y / 64;
			pos_r_mp = pos_r_my * map->size_x + pos_r_mx;
			if (pos_r_mp < map->size_x * map->size_y && map->blocks[pos_r_mp]->type == 1)
				stop = 8;
			else
			{
				printf("Avant : pos_x = %f, x_offset = %f\n", pos_x, x_offset);
				pos_x += x_offset;
				printf("Après : pos_x = %f\n", pos_x);
				// tmp->pos_y += tmp->y_offset;
				stop +=1;				
			}
			fprintf(stdin, "debug6\n");
		}
		fprintf(stdin, "debug7\n");
		write(1, "ok", 2);
		// tmp->distance = sqrt(pow(pos_x - map->player.x, 2) + pow(pos_y - map->player.y, 2));
		fprintf(stdin, "\ndebug8\n");
		i++;
		// tmp = tmp->next;
	// }

	// while (i < RAYS_COUNT)
	// {
	// 	// Check Vertical ray
	// }
	// printf("Out here\n");
	
  return (0);
}
