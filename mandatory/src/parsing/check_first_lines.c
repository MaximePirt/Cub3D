/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_first_lines.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/01 02:39:33 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/10 19:48:14 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Check if the block is already set
 * @param args the parse map
 * @param images tab which store images adress
 * @param index the index
 * @return int 1 if error, 0 if success
 */
int	check_doublons(t_parse_map **args, char ***images, int index)
{
	if (index < 8 && (*images)[index] != NULL)
	{
		ft_fprintf(STDERR_FILENO, "Error: %s already set\n", (*args)->blocks);
		return (1);
	}
	(*images)[index] = ft_strdup((*args)->blocks);
	return (0);
}

/**
 * @brief Check if the block is a param key (NO, SO, WE, EA, F, C)
 * @param to_copy the parse map
 * @param images the images
 * @return int 1 if error, 0 if success
 * TODO: This version is for bonus,
		to mandatory need to change args to 7 and remove DOOR
 */
int	is_param_key(t_parse_map **to_copy, char ***images)
{
	if ((ft_strncmp((*to_copy)->blocks, "NO", 2) == 0
			&& !check_doublons(to_copy, images, 0))
		|| (ft_strncmp((*to_copy)->blocks, "SO", 2) == 0
			&& !check_doublons(to_copy, images, 1))
		|| (ft_strncmp((*to_copy)->blocks, "WE", 2) == 0
			&& !check_doublons(to_copy, images, 2))
		|| (ft_strncmp((*to_copy)->blocks, "EA", 2) == 0
			&& !check_doublons(to_copy, images, 3))
		|| (ft_strncmp((*to_copy)->blocks, "F", 1) == 0
			&& !check_doublons(to_copy, images, 4))
		|| (ft_strncmp((*to_copy)->blocks, "C", 1) == 0
			&& !check_doublons(to_copy, images, 5))
		|| (ft_strncmp((*to_copy)->blocks, "DOOR", 4) == 0 //TODO: This is for bonus
			&& !check_doublons(to_copy, images, 6))
		|| (ft_strncmp((*to_copy)->blocks, "RIGHT_HAND", 10) == 0 //TODO: This is for bonus
			&& !check_doublons(to_copy, images, 7)))
		return (1);
	return (0);
}

/**
 * @brief Get the firsts files lines and compare it to maps options
 * @param to_copy the parse map
 * @param map the map
 *	TODO: This version is for bonus,
		to mandatory need to change args to 7 and remove DOOR
 * @return int
 */
int	checking_firsts_map_lines(t_parse_map **to_copy, char ***images)
{
	int	args;

	args = 8;
	while (to_copy && args > 0)
	{
		if (is_param_key(to_copy, images))
			args--;
		else if (ft_strncmp((*to_copy)->blocks, "\n", 1) != 0)
			break ;
		(*to_copy) = (*to_copy)->next;
	}
	if (args > 0)
	{
		ft_fprintf(STDERR_FILENO, "Error: Firsts lines can only contains"
			"NO, SO, WE, EA, F,C or \\n, one of each only\n");
		return (1);
	}
	return (0);
}
