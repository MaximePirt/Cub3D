/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:13 by mpierrot          #+#    #+#             */
/*   Updated: 2024/11/30 22:42:39 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
 * @brief Check if the file name is valid
 * @param file the file name
 * @return int
 */
int	parsing_map(char *filename)
{
	if (check_name(filename))
	{
		ft_fprintf(2, "Error : filename doesn't respect the subject\n");
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
	line = get_next_line(fd);
	if (line == NULL)
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
	parse_map_addback(&parse_map, parse_map_new("\n"));				//Line added to avoid segfault, easier to parse map
	free(line);														// due to possibilities to eof just after map or not
	close(fd);
	return (tmp);
}

void	free_parse_map(t_parse_map *map)
{
	t_parse_map	*tmp;

	while (map)
	{
		tmp = map;
		map = map->next;
		free(tmp->blocks);
		free(tmp);
	}
}

int	check_doublons(t_parse_map **args, char ***images, int index)
{
	if (index < 8 && (*images)[index] != NULL)
	{
		ft_fprintf(2, "Error: %s already set\n", (*args)->blocks);
		return (1);
	}
	(*images)[index] = ft_strdup((*args)->blocks);
	return (0);
}

/**
 * @brief Get the firsts files lines and compare it to maps options
 * @param to_copy the parse map
 * @param map the map
 *	TODO: When i will send the data map (ex NO data),
		check if data is already set, if so, return error
 *		it will prevent parsing error like 6 args but twice NO
 *	TODO: Check w Julien how to send the args data to his code's part
 *	TODO: This version is for bonus,
		to mandatory need to change args to 7 and remove DOOR
 * @return int
 */
int	checking_firsts_map_lines(t_parse_map **to_copy, char ***images)
{
	int	args;

	args = 7;
	while (to_copy && args > 0)
	{
		//    ft_printf("to_copy->blocks : [%s]\n", (*to_copy)->blocks);
		if (ft_strncmp((*to_copy)->blocks, "NO", 2) == 0
			&& !check_doublons(to_copy, images, 0)
			|| ft_strncmp((*to_copy)->blocks, "SO", 2) == 0
			&& !check_doublons(to_copy, images, 1)
			|| ft_strncmp((*to_copy)->blocks, "WE", 2) == 0
			&& !check_doublons(to_copy, images, 2)
			|| ft_strncmp((*to_copy)->blocks, "EA", 2) == 0
			&& !check_doublons(to_copy, images, 3)
			|| ft_strncmp((*to_copy)->blocks, "F", 1) == 0
			&& !check_doublons(to_copy, images, 4)
			|| ft_strncmp((*to_copy)->blocks, "C", 1) == 0
			&& !check_doublons(to_copy, images, 5)
			|| ft_strncmp((*to_copy)->blocks, "DOOR", 4) == 0
			&& !check_doublons(to_copy, images, 6))
			args--;
		else if (ft_strncmp((*to_copy)->blocks, "\n", 1) != 0)
			break ;
		(*to_copy) = (*to_copy)->next;
	}
	if (args > 0)
	{
		ft_printf("Error: Firsts lines can only contains NO, SO, WE, EA, F,"
			"C or \\n, one of each only\n");
		return (1);
	}
	return (0);
}

int	copy_tab_to_map(t_parse_map *to_copy, t_map *map, char ***images)
{
	int	i;
	int	j;
	int	max_size;
    int player_nb;

	i = 0;
    player_nb = 0;
	if (checking_firsts_map_lines(&to_copy, images))
		return (1);
	max_size = parse_map_max_size(to_copy);
	while (ft_strncmp(to_copy->blocks, "\n", 1) == 0)
		to_copy = to_copy->next;
	while (to_copy)
	{
		j = 0;
		while (to_copy->blocks[j])
		{
			if (to_copy->blocks[j] == '1')
				map->blocks[i][j].type = WALL;
			else if (to_copy->blocks[j] == '0')
				map->blocks[i][j].type = FLOOR;
			else if (to_copy->blocks[j] == ' ')
				map->blocks[i][j].type = VOID;
			else if (to_copy->blocks[j] == 'D')
			{
				map->blocks[i][j].type = DOOR;
				map->blocks[i][j].status = 1;
			}
			else if (to_copy->blocks[j] == 'N' || to_copy->blocks[j] == 'S'
				|| to_copy->blocks[j] == 'E' || to_copy->blocks[j] == 'W')
			{
				map->blocks[i][j].type = FLOOR;
				map->player.x = i;
				map->player.y = j;
                player_nb++;
				if (to_copy->blocks[j] == 'N')
					map->player.dir = 0;
				else if (to_copy->blocks[j] == 'E')
					map->player.dir = 90;
				else if (to_copy->blocks[j] == 'S')
					map->player.dir = 180;
				else if (to_copy->blocks[j] == 'W')
					map->player.dir = 270;
			}
			else if (to_copy->blocks[j] == '\n')
				break ;
			else if (to_copy->blocks[j])
			{
				ft_printf("Error: invalid character in map : [%c]\n",
					to_copy->blocks[j]);
				return (1);
			}
			j++;
		}
		while (j < max_size)
		{
			map->blocks[i][j].type = VOID;
			j++;
		}
		i++;
		to_copy = to_copy->next;
	}
    if (player_nb != 1)
    {
        ft_printf("Error: no player or too many players\n");
        return (1);
    }
	return (0);
}

void	print_enum_map(t_map *map)
{
	int	i;
	int	j;

	i = 0;
	while (i < map->size_y)
	{
		j = 0;
		while (j < map->size_x)
		{
			if (map->blocks[i][j].type == VOID)
				ft_printf("V");
			else if (map->blocks[i][j].type == FLOOR)
				ft_printf("0");
			else if (map->blocks[i][j].type == WALL)
				ft_printf("1");
			else if (map->blocks[i][j].type == DOOR)
				ft_printf("D");
            else if (map->blocks[i][j].type == FILL)
                ft_printf("F");
			j++;
		}
		ft_printf("\n");
		i++;
	}
}

void	find_map_start(t_parse_map **parse_map)
{
	while (*parse_map)
	{
		if (ft_strncmp((*parse_map)->blocks, "111", 3) == 0)
			break ;
		*parse_map = (*parse_map)->next;
	}
}

int	check_map(t_map *map, char *filename, char ***images)
{
	t_parse_map *parse_map;
	t_parse_map *tmp;

	parse_map = fill_map(filename);
	if (parse_map == NULL)
		return (1);
	tmp = parse_map;
	find_map_start(&tmp);
	printf("parse_map_size : %d\n", parse_map_size(tmp));
	printf("parse_map_max_size : %d\n", parse_map_max_size(tmp));
	map = ft_init_map(parse_map_max_size(tmp), parse_map_size(tmp));
	if (map == NULL)
		return (1);
	if (copy_tab_to_map(parse_map, map, images))
		return (1);
    if (preptoflood(map))
        return (1);

	free_parse_map(parse_map);

	return (0);
}