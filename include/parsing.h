#ifndef PARSING_H
#define PARSING_H

#include "struct.h"

int     check_name(char *file);
int		parsing_map(char *filename);
int		check_map(t_map *map, char *filename, char ***images);

/////////////////////////floodfill///////////////////////////
int		preptoflood(t_map *map);


/////////////////////////lst_parsing/////////////////////////
t_parse_map	*parsemaplast(t_parse_map *lst);
void	parse_map_addback(t_parse_map **lst, t_parse_map *new);
int	parse_map_size(t_parse_map *lst);
t_parse_map *fill_map(char *filename);
void	print_parse_map(t_parse_map *lst);
t_parse_map	*parse_map_new(char *line);
int	parse_map_max_size(t_parse_map *lst);


//////////DEBUG////////////
void	print_enum_map(t_map *map);

#endif