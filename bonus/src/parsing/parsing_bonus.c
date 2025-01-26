/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:13 by mpierrot          #+#    #+#             */
/*   Updated: 2025/01/27 00:25:21 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube_bonus.h"

/**
 * @brief Check the map and fill the map struct
 * @param map
 * @param filename the filename
 * @param images the images
 * @return int 1 if error, 0 if success
 */
int	check_map(t_map **map, char *filename, char ***images)
{
	t_parse_map	*parse_map;
	t_parse_map	*tmp;

	parse_map = fill_map(filename);
	if (parse_map == NULL)
		return (1);
	tmp = parse_map;
	find_map_start(&tmp);
	*map = ft_init_map(parse_map_max_size(tmp), parse_map_size(tmp));
	if (*map == NULL)
	{
		free_parse_map(parse_map);
		return (1);
	}
	if (copy_tab_to_map(parse_map, *map, images) || preptoflood(*map))
	{
		free_parse_map(parse_map);
		return (1);
	}
	free_parse_map(parse_map);
	return (0);
}

int	check_name(char *file)
{
	int		i;
	int		filename_len;
	char	str[5];

	if (!file)
		return (1);
	str[0] = '.';
	str[1] = 'c';
	str[2] = 'u';
	str[3] = 'b';
	str[4] = '\0';
	i = 0;
	while (file[i])
		i++;
	if (i <= 4)
		return (1);
	filename_len = ft_strlen(file);
	i = ft_strcmp(file + (filename_len - 4), str);
	if (i != 0)
		return (1);
	return (0);
}

/**
 * @brief Find the start of the map in the 
 * 			parse map searching at least 3 '1' in a row
 * @param parse_map the parse map
 * @return void
 */
void	find_map_start(t_parse_map **parse_map)
{
	while (*parse_map)
	{
		if (ft_strchr((*parse_map)->blocks, '1') == 0)
			break ;
		*parse_map = (*parse_map)->next;
	}
}

static int first_read(int fd, char **line)
{
	*line = get_next_line(fd);
	if (*line == NULL)
	{
		close(fd);
		return (1);
	}
	return (0);
}

/**
 * @brief Fill parse map with gnl
 * @param filename the map used to fill the parse map
 * @return t_parse_map*
 */
t_parse_map	*fill_map(char *filename)
{
	t_parse_map	*parse_map;
	t_parse_map	*tmp;
	char		*line;
	int			fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
		return (NULL);
	if (first_read(fd, &line))
		return (NULL);
	parse_map = parse_map_new(line);
	tmp = parse_map;
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		if (line == NULL)
			break ;
		parse_map_addback(&parse_map, parse_map_new(line));
	}
	parse_map_addback(&parse_map, parse_map_new("\n"));
	free(line);
	close(fd);
	return (tmp);
}
