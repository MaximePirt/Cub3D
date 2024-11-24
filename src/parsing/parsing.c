/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mpierrot <mpierrot@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/16 20:01:13 by mpierrot          #+#    #+#             */
/*   Updated: 2024/11/24 04:35:03 by mpierrot         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"

/**
* @brief Check if the file name is valid
* @param file the file name
* @return int
*/
int parsing_map(char *filename)
{
  if (check_name(filename))
  {
    ft_fprintf(2, "Error\n");
    return (1);
  }
  return (0);
}

/**
* @brief Fill parse map with gnl
* @param filename the map used to fill the parse map
* @return t_parse_map*
*/
t_parse_map *fill_map(char *filename)
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
            break;
		parse_map_addback(&parse_map, parse_map_new(line));
    }
   free(line);
   close(fd);
   return (tmp);
}

void tabprint(char **tab)
{
    int i;

    i = 0;
    while (tab[i])
    {
        ft_printf("%s", tab[i]);
        i++;
    }
}

char **convert_lst_to_tab(t_parse_map *parse_map)
{
	char **tab;
    int i;

    i = 0;
    tab = malloc(sizeof(char *) * (parse_map_size(parse_map) + 1));
    if (tab == NULL)
        return (NULL);
    while (parse_map)
    {
        tab[i] = ft_strdup(parse_map->blocks);
        i++;
        parse_map = parse_map->next;
    }
    tab[i] = NULL;
//    tabprint(tab);
    return (tab);
}

void free_parse_map(t_parse_map *map)
{
    t_parse_map *tmp;

    while (map)
    {
        tmp = map;
        map = map->next;
        free(tmp->blocks);
        free(tmp);
    }
}

/**
* @brief Get the firsts files lines and compare it to maps options
* @param to_copy the parse map
* @param map the map
*	TODO: When i will send the data map (ex NO data), check if data is already set, if so, return error
*		it will prevent parsing error like 6 args but twice NO
*	TODO: Check w Julien how to send the args data to his code's part
* @return int
*/
int	checking_firsts_map_lines(t_parse_map *to_copy, t_map *map)
{
  int	args;
  (void)map;

  args = 6;
  while (to_copy && args > 0)
  {
    if (ft_strncmp(to_copy->blocks, "NO", 2) == 0)
      args--;
    else if (ft_strncmp(to_copy->blocks, "SO", 2) == 0)
      args--;
    else if (ft_strncmp(to_copy->blocks, "WE", 2) == 0)
      args--;
    else if (ft_strncmp(to_copy->blocks, "EA", 2) == 0)
      args--;
    else if (ft_strncmp(to_copy->blocks, "F", 1) == 0)
      args--;
    else if (ft_strncmp(to_copy->blocks, "C", 1) == 0)
      args--;
    else if (!ft_strncmp(to_copy->blocks, "\n", 1) == 0)
      break;
    to_copy = to_copy->next;
  }
  if (args > 0)
  {
    ft_printf("Error: Firsts lines can only contains NO, SO, WE, EA, F, C or \\n\n");
    return (1);
  }
  return (0);
}

int copy_tab_to_map(t_parse_map *to_copy, t_map *map)
{
    int i;
    int j;
    int max_size;

    i = 0;
    max_size = parse_map_max_size(to_copy);
    if (checking_firsts_map_lines(to_copy, map))
        return (1);
    ft_printf("Firsts lines are ok\n");
    ft_printf("Here is to copy blocks [%c]\n", to_copy->blocks[0]);
    while (to_copy)
    {
        j = 0;
        while (to_copy->blocks)
        {
			if (to_copy->blocks[j] == '1')
				map->blocks[i][j].type = WALL;
			else if (to_copy->blocks[j] == '0')
				map->blocks[i][j].type = FLOOR;
			else if (to_copy->blocks[j] == ' ')
				map->blocks[i][j].type = VOID;
			else if (to_copy->blocks[j] == 'D')
                map->blocks[i][j].type = DOOR;
            else if (to_copy->blocks[j] == 'N'|| to_copy->blocks[j] == 'S'
				|| to_copy->blocks[j] == 'E'|| to_copy->blocks[j] == 'W')
            {
                map->blocks[i][j].type = FLOOR;
                map->player.x = i;
                map->player.y = j;
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
                break;
            else
			{
                ft_printf("Error: invalid character in map\n");
                exit(1);
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
    return (0);
}

void print_enum_map(t_map *map)
{
    int i;
    int j;

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
            j++;
        }
        ft_printf("\n");
        i++;
    }
}


int check_map(t_map *map, char *filename)
{
	t_parse_map *parse_map;

    parse_map = fill_map(filename);
    if (parse_map == NULL)
		return (1);
    map = ft_init_map(parse_map_max_size(parse_map), parse_map_size(parse_map));
	if (map == NULL)
        return (1);
    if (copy_tab_to_map(parse_map, map))
		return (1);
	print_enum_map(map);

    free_parse_map(parse_map);

	return (0);
}