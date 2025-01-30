/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lst_pars_lib.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/24 00:39:38 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/26 20:55:36 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Create a new parse map
 * @param block the block to add to the parse map
 * @return t_parse_map*
 */
t_parse_map	*parse_map_new(char *block)
{
	t_parse_map	*new;

	new = 0;
	new = malloc(sizeof(t_parse_map));
	if (new == NULL)
		return (NULL);
	new->blocks = ft_strdup(block);
	if (new->blocks == NULL)
	{
		free(new);
		return (NULL);
	}
	new->blocks_len = ft_strlen(new->blocks);
	new->next = NULL;
	return (new);
}

/**
 * @brief Get the last parse map
 * @param lst the parse map
 * @return t_parse_map*
 */
t_parse_map	*parsemaplast(t_parse_map *lst)
{
	if (!lst)
		return (NULL);
	while (lst)
	{
		if (lst->next == NULL)
			return (lst);
		lst = lst->next;
	}
	return (lst);
}

/**
 * @brief Add a new parse map to the end of the list
 * @param lst the parse map
 * @param new the new parse map to add
 */
void	parse_map_addback(t_parse_map **lst, t_parse_map *new)
{
	t_parse_map	*tmp;

	if (!new || !lst)
		return ;
	if (*lst)
	{
		tmp = parsemaplast(*lst);
		tmp->next = new;
	}
	else
		*lst = new;
}

/**
 * @brief Parse map size
 * @param lst the parse map
 * @return int
 */
int	parse_map_size(t_parse_map *lst)
{
	int			i;
	t_parse_map	*tmp;

	tmp = lst;
	i = 0;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

int	parse_map_max_size(t_parse_map *lst)
{
	t_parse_map	*tmp;
	int			i;

	i = 0;
	tmp = lst;
	while (tmp)
	{
		if (tmp->blocks_len > i)
			i = tmp->blocks_len;
		tmp = tmp->next;
	}
	return (i);
}
