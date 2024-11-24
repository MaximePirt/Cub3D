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
	new->max_len = 0;
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
        if (new->blocks_len > tmp->max_len)
            tmp->max_len = new->blocks_len;
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
	int		i;
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
    parse_map_addback(&parse_map, parse_map_new(line));
    tmp = parse_map;
	while (line)
    {
        line = get_next_line(fd);
        if (line == NULL)
            break;
		parse_map_addback(&parse_map, parse_map_new(line));
    }
   close(fd);
   return (tmp);
}

/**
* @brief Print the parsed map
*	TODO: Delet, this function is only for debug
*/
void	print_parse_map(t_parse_map *map)
{
	t_parse_map *tmp;

	tmp = map;
	while (tmp)
	{
		ft_printf("%s", tmp->blocks);
        tmp = tmp->next;
	}
	return ;
}

int check_map(t_map *map, char *filename)
{
  	(void)map;
	t_parse_map *parse_map;

    parse_map = fill_map(filename);
    if (parse_map == NULL)
		return (1);
	print_parse_map(parse_map);
	ft_printf("\nLen = %d\n", parse_map_size(parse_map));
	return (0);
}