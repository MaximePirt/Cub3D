#ifndef PARSING_H
#define PARSING_H

int     check_name(char *file);
void	oh_problems(t_map *map, char *str, int i, int fd);
void	check_size(t_map *map);
void	filltab(t_map *map);
void	flood_fill(t_map *map, int x, int y);
void	where_start_fill(t_map *map);
void	check_min_inputs(t_map *map);
t_map	*preptoflood(char *str);
void	exit_func(int fd, t_map *lst, char **tab, int error_code);
int     hm_compo(char **tab);
void	clean_flood(t_map *map);
void	copy_map_to_mapfill(t_map *map);
int		parsing_map(char *filename);


#endif