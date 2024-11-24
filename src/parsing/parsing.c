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